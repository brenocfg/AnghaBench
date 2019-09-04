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
typedef  size_t u32 ;
struct sumo_disp_clock_voltage_mapping_table {scalar_t__* display_clock_frequency; size_t num_max_voltage_levels; } ;
struct radeon_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ ulMaximumSupportedCLK; } ;
typedef  TYPE_1__ ATOM_CLK_VOLT_CAPABILITY ;

/* Variables and functions */
 size_t SUMO_MAX_NUMBER_VOLTAGES ; 

__attribute__((used)) static void sumo_construct_display_voltage_mapping_table(struct radeon_device *rdev,
							 struct sumo_disp_clock_voltage_mapping_table *disp_clk_voltage_mapping_table,
							 ATOM_CLK_VOLT_CAPABILITY *table)
{
	u32 i;

	for (i = 0; i < SUMO_MAX_NUMBER_VOLTAGES; i++) {
		if (table[i].ulMaximumSupportedCLK == 0)
			break;

		disp_clk_voltage_mapping_table->display_clock_frequency[i] =
			table[i].ulMaximumSupportedCLK;
	}

	disp_clk_voltage_mapping_table->num_max_voltage_levels = i;

	if (disp_clk_voltage_mapping_table->num_max_voltage_levels == 0) {
		disp_clk_voltage_mapping_table->display_clock_frequency[0] = 80000;
		disp_clk_voltage_mapping_table->num_max_voltage_levels = 1;
	}
}