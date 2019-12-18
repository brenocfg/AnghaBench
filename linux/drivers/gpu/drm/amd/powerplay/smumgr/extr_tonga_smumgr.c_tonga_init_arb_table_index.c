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
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  arb_table_start; } ;
struct tonga_smumgr {TYPE_1__ smu7_data; } ;
struct pp_hwmgr {scalar_t__ smu_backend; } ;

/* Variables and functions */
 scalar_t__ MC_CG_ARB_FREQ_F1 ; 
 int /*<<< orphan*/  SMC_RAM_END ; 
 int smu7_read_smc_sram_dword (struct pp_hwmgr*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int smu7_write_smc_sram_dword (struct pp_hwmgr*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tonga_init_arb_table_index(struct pp_hwmgr *hwmgr)
{
	struct tonga_smumgr *smu_data = (struct tonga_smumgr *)(hwmgr->smu_backend);
	uint32_t tmp;
	int result;

	/*
	* This is a read-modify-write on the first byte of the ARB table.
	* The first byte in the SMU72_Discrete_MCArbDramTimingTable structure
	* is the field 'current'.
	* This solution is ugly, but we never write the whole table only
	* individual fields in it.
	* In reality this field should not be in that structure
	* but in a soft register.
	*/
	result = smu7_read_smc_sram_dword(hwmgr,
				smu_data->smu7_data.arb_table_start, &tmp, SMC_RAM_END);

	if (result != 0)
		return result;

	tmp &= 0x00FFFFFF;
	tmp |= ((uint32_t)MC_CG_ARB_FREQ_F1) << 24;

	return smu7_write_smc_sram_dword(hwmgr,
			smu_data->smu7_data.arb_table_start, tmp, SMC_RAM_END);
}