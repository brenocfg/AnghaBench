#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_14__ {int /*<<< orphan*/  arb_table_start; } ;
struct tonga_smumgr {TYPE_6__ smu7_data; } ;
struct TYPE_12__ {size_t count; TYPE_3__* dpm_levels; } ;
struct TYPE_10__ {size_t count; TYPE_1__* dpm_levels; } ;
struct TYPE_13__ {TYPE_4__ mclk_table; TYPE_2__ sclk_table; } ;
struct smu7_hwmgr {TYPE_5__ dpm_table; } ;
struct pp_hwmgr {scalar_t__ smu_backend; scalar_t__ backend; } ;
struct TYPE_15__ {int /*<<< orphan*/ ** entries; } ;
struct TYPE_11__ {int /*<<< orphan*/  value; } ;
struct TYPE_9__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_7__ SMU72_Discrete_MCArbDramTimingTable ;

/* Variables and functions */
 int /*<<< orphan*/  SMC_RAM_END ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int,int) ; 
 int smu7_copy_bytes_to_smc (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int tonga_populate_memory_timing_parameters (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tonga_program_memory_timing_parameters(struct pp_hwmgr *hwmgr)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	struct tonga_smumgr *smu_data =
				(struct tonga_smumgr *)(hwmgr->smu_backend);
	int result = 0;
	SMU72_Discrete_MCArbDramTimingTable  arb_regs;
	uint32_t i, j;

	memset(&arb_regs, 0x00, sizeof(SMU72_Discrete_MCArbDramTimingTable));

	for (i = 0; i < data->dpm_table.sclk_table.count; i++) {
		for (j = 0; j < data->dpm_table.mclk_table.count; j++) {
			result = tonga_populate_memory_timing_parameters
				(hwmgr, data->dpm_table.sclk_table.dpm_levels[i].value,
				 data->dpm_table.mclk_table.dpm_levels[j].value,
				 &arb_regs.entries[i][j]);

			if (result)
				break;
		}
	}

	if (!result) {
		result = smu7_copy_bytes_to_smc(
				hwmgr,
				smu_data->smu7_data.arb_table_start,
				(uint8_t *)&arb_regs,
				sizeof(SMU72_Discrete_MCArbDramTimingTable),
				SMC_RAM_END
				);
	}

	return result;
}