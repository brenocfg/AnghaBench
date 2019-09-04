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
typedef  int u32 ;
struct ci_single_dpm_table {int count; TYPE_1__* dpm_levels; } ;
struct TYPE_2__ {scalar_t__ enabled; } ;

/* Variables and functions */

__attribute__((used)) static u32 ci_get_dpm_level_enable_mask_value(struct ci_single_dpm_table *dpm_table)
{
	u32 i;
	u32 mask_value = 0;

	for (i = dpm_table->count; i > 0; i--) {
		mask_value = mask_value << 1;
		if (dpm_table->dpm_levels[i-1].enabled)
			mask_value |= 0x1;
		else
			mask_value &= 0xFFFFFFFE;
	}

	return mask_value;
}