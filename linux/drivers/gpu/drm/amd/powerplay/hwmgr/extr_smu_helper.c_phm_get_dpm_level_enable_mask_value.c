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
struct vi_dpm_table {int count; TYPE_1__* dpm_level; } ;
typedef  int int32_t ;
struct TYPE_2__ {scalar_t__ enabled; } ;

/* Variables and functions */

int32_t phm_get_dpm_level_enable_mask_value(void *table)
{
	int32_t i;
	int32_t mask = 0;
	struct vi_dpm_table *dpm_table = (struct vi_dpm_table *)table;

	for (i = dpm_table->count; i > 0; i--) {
		mask = mask << 1;
		if (dpm_table->dpm_level[i - 1].enabled)
			mask |= 0x1;
		else
			mask &= 0xFFFFFFFE;
	}

	return mask;
}