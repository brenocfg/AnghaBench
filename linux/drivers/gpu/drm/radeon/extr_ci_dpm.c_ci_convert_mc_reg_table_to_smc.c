#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct radeon_device {int dummy; } ;
struct TYPE_7__ {size_t count; TYPE_1__* dpm_levels; } ;
struct TYPE_8__ {TYPE_2__ mclk_table; } ;
struct ci_power_info {TYPE_3__ dpm_table; } ;
struct TYPE_9__ {int /*<<< orphan*/ * data; } ;
struct TYPE_6__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_4__ SMU7_Discrete_MCRegisters ;

/* Variables and functions */
 int /*<<< orphan*/  ci_convert_mc_reg_table_entry_to_smc (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void ci_convert_mc_reg_table_to_smc(struct radeon_device *rdev,
					   SMU7_Discrete_MCRegisters *mc_reg_table)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	u32 i;

	for (i = 0; i < pi->dpm_table.mclk_table.count; i++)
		ci_convert_mc_reg_table_entry_to_smc(rdev,
						     pi->dpm_table.mclk_table.dpm_levels[i].value,
						     &mc_reg_table->data[i]);
}