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
struct amdgpu_clock_voltage_dependency_table {scalar_t__ count; TYPE_1__* entries; } ;
struct TYPE_2__ {size_t clk; } ;

/* Variables and functions */

__attribute__((used)) static void btc_get_max_clock_from_voltage_dependency_table(struct amdgpu_clock_voltage_dependency_table *table,
							    u32 *max_clock)
{
	u32 i, clock = 0;

	if ((table == NULL) || (table->count == 0)) {
		*max_clock = clock;
		return;
	}

	for (i = 0; i < table->count; i++) {
		if (clock < table->entries[i].clk)
			clock = table->entries[i].clk;
	}
	*max_clock = clock;
}