#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int size; } ;
struct TYPE_13__ {int size; } ;
struct TYPE_12__ {int size; } ;
struct TYPE_11__ {int size; } ;
struct TYPE_10__ {int size; } ;
struct TYPE_9__ {TYPE_1__* driver; void* current_size; } ;
struct TYPE_8__ {int size_type; } ;

/* Variables and functions */
 TYPE_7__* A_SIZE_16 (void*) ; 
 TYPE_6__* A_SIZE_32 (void*) ; 
 TYPE_5__* A_SIZE_8 (void*) ; 
 TYPE_4__* A_SIZE_FIX (void*) ; 
 TYPE_3__* A_SIZE_LVL2 (void*) ; 
#define  FIXED_APER_SIZE 132 
#define  LVL2_APER_SIZE 131 
#define  U16_APER_SIZE 130 
#define  U32_APER_SIZE 129 
#define  U8_APER_SIZE 128 
 TYPE_2__* agp_bridge ; 
 int agp_memory_reserved ; 

__attribute__((used)) static int agp_return_size(void)
{
	int current_size;
	void *temp;

	temp = agp_bridge->current_size;

	switch (agp_bridge->driver->size_type) {
	case U8_APER_SIZE:
		current_size = A_SIZE_8(temp)->size;
		break;
	case U16_APER_SIZE:
		current_size = A_SIZE_16(temp)->size;
		break;
	case U32_APER_SIZE:
		current_size = A_SIZE_32(temp)->size;
		break;
	case LVL2_APER_SIZE:
		current_size = A_SIZE_LVL2(temp)->size;
		break;
	case FIXED_APER_SIZE:
		current_size = A_SIZE_FIX(temp)->size;
		break;
	default:
		current_size = 0;
		break;
	}

	current_size -= (agp_memory_reserved / (1024*1024));
	if (current_size <0)
		current_size = 0;
	return current_size;
}