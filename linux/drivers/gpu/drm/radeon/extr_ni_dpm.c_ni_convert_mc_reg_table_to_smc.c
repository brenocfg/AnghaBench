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
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;
struct ni_ps {int performance_level_count; int /*<<< orphan*/ * performance_levels; } ;
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ SMC_NIslands_MCRegisters ;

/* Variables and functions */
 int NISLANDS_MCREGISTERTABLE_FIRST_DRIVERSTATE_SLOT ; 
 int /*<<< orphan*/  ni_convert_mc_reg_table_entry_to_smc (struct radeon_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ni_ps* ni_get_ps (struct radeon_ps*) ; 

__attribute__((used)) static void ni_convert_mc_reg_table_to_smc(struct radeon_device *rdev,
					   struct radeon_ps *radeon_state,
					   SMC_NIslands_MCRegisters *mc_reg_table)
{
	struct ni_ps *state = ni_get_ps(radeon_state);
	int i;

	for (i = 0; i < state->performance_level_count; i++) {
		ni_convert_mc_reg_table_entry_to_smc(rdev,
						     &state->performance_levels[i],
						     &mc_reg_table->data[NISLANDS_MCREGISTERTABLE_FIRST_DRIVERSTATE_SLOT + i]);
	}
}