#include <iostream>
#include <stdint.h>
#include "ipc_server.h"
#include "topics/test_topic.h"
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>

IpcServer::~IpcServer(){}
IpcServer::IpcServer()
{
    using namespace boost::interprocess;

    Test::TestTopic topic;
    topic.name = "TestTopic";
    topic.message = "Testing";

    shared_memory_object shdmem( open_or_create, "Test", read_write );
    shdmem.truncate( sizeof( topic ));

    mapped_region region( shdmem, read_write );

    int* write_address = static_cast<int*>( region.get_address() );
    *write_address = 99;

    mapped_region region2( shdmem, read_only );
    int* read_address = static_cast<int*>( region.get_address() );
    std::cout << *read_address << std::endl;
}
