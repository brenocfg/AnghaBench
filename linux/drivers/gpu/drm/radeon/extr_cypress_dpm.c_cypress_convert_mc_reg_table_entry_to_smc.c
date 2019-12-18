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
typedef  size_t u32 ;
struct rv7xx_pl {scalar_t__ mclk; } ;
struct radeon_device {int dummy; } ;
struct TYPE_3__ {size_t num_entries; int /*<<< orphan*/  valid_flag; int /*<<< orphan*/  last; TYPE_2__* mc_reg_table_entry; } ;
struct evergreen_power_info {TYPE_1__ mc_reg_table; } ;
struct TYPE_4__ {scalar_t__ mclk_max; } ;
typedef  int /*<<< orphan*/  SMC_Evergreen_MCRegisterSet ;

/* Variables and functions */
 int /*<<< orphan*/  cypress_convert_mc_registers (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void cypress_convert_mc_reg_table_entry_to_smc(struct radeon_device *rdev,
						      struct rv7xx_pl *pl,
						      SMC_Evergreen_MCRegisterSet *mc_reg_table_data)
{
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	u32 i = 0;

	for (i = 0; i < eg_pi->mc_reg_table.num_entries; i++) {
		if (pl->mclk <=
		    eg_pi->mc_reg_table.mc_reg_table_entry[i].mclk_max)
			break;
	}

	if ((i == eg_pi->mc_reg_table.num_entries) && (i > 0))
		--i;

	cypress_convert_mc_registers(&eg_pi->mc_reg_table.mc_reg_table_entry[i],
				     mc_reg_table_data,
				     eg_pi->mc_reg_table.last,
				     eg_pi->mc_reg_table.valid_flag);
}