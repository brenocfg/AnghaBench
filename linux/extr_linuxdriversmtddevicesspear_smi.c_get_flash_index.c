#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ device_id; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENODEV ; 
 TYPE_1__* flash_devices ; 

__attribute__((used)) static int get_flash_index(u32 flash_id)
{
	int index;

	/* Matches chip-id to entire list of 'serial-nor flash' ids */
	for (index = 0; index < ARRAY_SIZE(flash_devices); index++) {
		if (flash_devices[index].device_id == flash_id)
			return index;
	}

	/* Memory chip is not listed and not supported */
	return -ENODEV;
}