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
struct ci_single_dpm_table {TYPE_1__* dpm_levels; } ;
struct TYPE_2__ {size_t value; size_t param1; int enabled; } ;

/* Variables and functions */

__attribute__((used)) static void ci_setup_pcie_table_entry(struct ci_single_dpm_table* dpm_table,
				      u32 index, u32 pcie_gen, u32 pcie_lanes)
{
	dpm_table->dpm_levels[index].value = pcie_gen;
	dpm_table->dpm_levels[index].param1 = pcie_lanes;
	dpm_table->dpm_levels[index].enabled = true;
}