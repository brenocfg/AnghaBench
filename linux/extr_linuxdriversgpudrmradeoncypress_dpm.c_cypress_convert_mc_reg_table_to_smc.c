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
struct rv7xx_ps {int /*<<< orphan*/  high; int /*<<< orphan*/  medium; int /*<<< orphan*/  low; } ;
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ SMC_Evergreen_MCRegisters ;

/* Variables and functions */
 int /*<<< orphan*/  cypress_convert_mc_reg_table_entry_to_smc (struct radeon_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct rv7xx_ps* rv770_get_ps (struct radeon_ps*) ; 

__attribute__((used)) static void cypress_convert_mc_reg_table_to_smc(struct radeon_device *rdev,
						struct radeon_ps *radeon_state,
						SMC_Evergreen_MCRegisters *mc_reg_table)
{
	struct rv7xx_ps *state = rv770_get_ps(radeon_state);

	cypress_convert_mc_reg_table_entry_to_smc(rdev,
						  &state->low,
						  &mc_reg_table->data[2]);
	cypress_convert_mc_reg_table_entry_to_smc(rdev,
						  &state->medium,
						  &mc_reg_table->data[3]);
	cypress_convert_mc_reg_table_entry_to_smc(rdev,
						  &state->high,
						  &mc_reg_table->data[4]);
}