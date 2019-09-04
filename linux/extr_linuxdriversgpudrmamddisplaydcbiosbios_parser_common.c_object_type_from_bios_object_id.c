#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
#define  GRAPH_OBJECT_TYPE_CONNECTOR 132 
#define  GRAPH_OBJECT_TYPE_ENCODER 131 
#define  GRAPH_OBJECT_TYPE_GENERIC 130 
#define  GRAPH_OBJECT_TYPE_GPU 129 
#define  GRAPH_OBJECT_TYPE_ROUTER 128 
 int OBJECT_TYPE_CONNECTOR ; 
 int OBJECT_TYPE_ENCODER ; 
 int OBJECT_TYPE_GENERIC ; 
 int OBJECT_TYPE_GPU ; 
 int OBJECT_TYPE_MASK ; 
 int OBJECT_TYPE_ROUTER ; 
 int OBJECT_TYPE_SHIFT ; 
 int OBJECT_TYPE_UNKNOWN ; 

__attribute__((used)) static enum object_type object_type_from_bios_object_id(uint32_t bios_object_id)
{
	uint32_t bios_object_type = (bios_object_id & OBJECT_TYPE_MASK)
				>> OBJECT_TYPE_SHIFT;
	enum object_type object_type;

	switch (bios_object_type) {
	case GRAPH_OBJECT_TYPE_GPU:
		object_type = OBJECT_TYPE_GPU;
		break;
	case GRAPH_OBJECT_TYPE_ENCODER:
		object_type = OBJECT_TYPE_ENCODER;
		break;
	case GRAPH_OBJECT_TYPE_CONNECTOR:
		object_type = OBJECT_TYPE_CONNECTOR;
		break;
	case GRAPH_OBJECT_TYPE_ROUTER:
		object_type = OBJECT_TYPE_ROUTER;
		break;
	case GRAPH_OBJECT_TYPE_GENERIC:
		object_type = OBJECT_TYPE_GENERIC;
		break;
	default:
		object_type = OBJECT_TYPE_UNKNOWN;
		break;
	}

	return object_type;
}