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
struct vega12_single_dpm_table {size_t count; TYPE_1__* dpm_levels; } ;
struct TYPE_2__ {int enabled; } ;

/* Variables and functions */

__attribute__((used)) static uint32_t vega12_find_lowest_dpm_level(
		struct vega12_single_dpm_table *table)
{
	uint32_t i;

	for (i = 0; i < table->count; i++) {
		if (table->dpm_levels[i].enabled)
			break;
	}

	if (i >= table->count) {
		i = 0;
		table->dpm_levels[i].enabled = true;
	}

	return i;
}