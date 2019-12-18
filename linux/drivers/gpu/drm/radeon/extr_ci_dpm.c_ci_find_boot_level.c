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
typedef  size_t u32 ;
struct ci_single_dpm_table {size_t count; TYPE_1__* dpm_levels; } ;
struct TYPE_2__ {size_t value; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int ci_find_boot_level(struct ci_single_dpm_table *table,
			      u32 value, u32 *boot_level)
{
	u32 i;
	int ret = -EINVAL;

	for(i = 0; i < table->count; i++) {
		if (value == table->dpm_levels[i].value) {
			*boot_level = i;
			ret = 0;
		}
	}

	return ret;
}