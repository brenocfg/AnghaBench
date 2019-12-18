#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct vi_dpm_table {size_t count; TYPE_1__* dpm_level; } ;
struct TYPE_2__ {size_t value; } ;

/* Variables and functions */
 int EINVAL ; 

int phm_find_boot_level(void *table,
		uint32_t value, uint32_t *boot_level)
{
	int result = -EINVAL;
	uint32_t i;
	struct vi_dpm_table *dpm_table = (struct vi_dpm_table *)table;

	for (i = 0; i < dpm_table->count; i++) {
		if (value == dpm_table->dpm_level[i].value) {
			*boot_level = i;
			result = 0;
		}
	}

	return result;
}