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

/* Variables and functions */
#define  RTAS_TYPE_DEALLOC 134 
#define  RTAS_TYPE_DUMP 133 
#define  RTAS_TYPE_EPOW 132 
#define  RTAS_TYPE_INFO 131 
#define  RTAS_TYPE_IO 130 
#define  RTAS_TYPE_PLATFORM 129 
#define  RTAS_TYPE_PRRN 128 
 char** rtas_type ; 

__attribute__((used)) static char *rtas_event_type(int type)
{
	if ((type > 0) && (type < 11))
		return rtas_type[type];

	switch (type) {
		case RTAS_TYPE_EPOW:
			return "EPOW";
		case RTAS_TYPE_PLATFORM:
			return "Platform Error";
		case RTAS_TYPE_IO:
			return "I/O Event";
		case RTAS_TYPE_INFO:
			return "Platform Information Event";
		case RTAS_TYPE_DEALLOC:
			return "Resource Deallocation Event";
		case RTAS_TYPE_DUMP:
			return "Dump Notification Event";
		case RTAS_TYPE_PRRN:
			return "Platform Resource Reassignment Event";
	}

	return rtas_type[0];
}