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
typedef  size_t uint32_t ;
struct pp_hwmgr {scalar_t__ smu_backend; } ;
struct TYPE_3__ {size_t num_entries; int /*<<< orphan*/  validflag; int /*<<< orphan*/  last; TYPE_2__* mc_reg_table_entry; } ;
struct iceland_smumgr {TYPE_1__ mc_reg_table; } ;
struct TYPE_4__ {size_t const mclk_max; } ;
typedef  int /*<<< orphan*/  SMU71_Discrete_MCRegisterSet ;

/* Variables and functions */
 int /*<<< orphan*/  iceland_convert_mc_registers (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iceland_convert_mc_reg_table_entry_to_smc(struct pp_hwmgr *hwmgr,
		const uint32_t memory_clock,
		SMU71_Discrete_MCRegisterSet *mc_reg_table_data
		)
{
	struct iceland_smumgr *smu_data = (struct iceland_smumgr *)(hwmgr->smu_backend);
	uint32_t i = 0;

	for (i = 0; i < smu_data->mc_reg_table.num_entries; i++) {
		if (memory_clock <=
			smu_data->mc_reg_table.mc_reg_table_entry[i].mclk_max) {
			break;
		}
	}

	if ((i == smu_data->mc_reg_table.num_entries) && (i > 0))
		--i;

	iceland_convert_mc_registers(&smu_data->mc_reg_table.mc_reg_table_entry[i],
				mc_reg_table_data, smu_data->mc_reg_table.last,
				smu_data->mc_reg_table.validflag);

	return 0;
}