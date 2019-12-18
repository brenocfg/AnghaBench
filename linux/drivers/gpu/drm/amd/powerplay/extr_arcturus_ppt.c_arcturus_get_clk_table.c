#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct smu_context {int dummy; } ;
struct pp_clock_levels_with_latency {int num_levels; TYPE_2__* data; } ;
struct arcturus_single_dpm_table {int count; TYPE_1__* dpm_levels; } ;
struct TYPE_4__ {int clocks_in_khz; scalar_t__ latency_in_us; } ;
struct TYPE_3__ {int value; } ;

/* Variables and functions */
 int MAX_NUM_CLOCKS ; 

__attribute__((used)) static int arcturus_get_clk_table(struct smu_context *smu,
			struct pp_clock_levels_with_latency *clocks,
			struct arcturus_single_dpm_table *dpm_table)
{
	int i, count;

	count = (dpm_table->count > MAX_NUM_CLOCKS) ? MAX_NUM_CLOCKS : dpm_table->count;
	clocks->num_levels = count;

	for (i = 0; i < count; i++) {
		clocks->data[i].clocks_in_khz =
			dpm_table->dpm_levels[i].value * 1000;
		clocks->data[i].latency_in_us = 0;
	}

	return 0;
}