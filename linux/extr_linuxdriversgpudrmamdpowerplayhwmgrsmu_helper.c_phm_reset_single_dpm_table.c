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
typedef  int uint32_t ;
struct vi_dpm_table {int count; TYPE_1__* dpm_level; } ;
struct TYPE_2__ {int enabled; } ;

/* Variables and functions */

int phm_reset_single_dpm_table(void *table,
				uint32_t count, int max)
{
	int i;

	struct vi_dpm_table *dpm_table = (struct vi_dpm_table *)table;

	dpm_table->count = count > max ? max : count;

	for (i = 0; i < dpm_table->count; i++)
		dpm_table->dpm_level[i].enabled = false;

	return 0;
}