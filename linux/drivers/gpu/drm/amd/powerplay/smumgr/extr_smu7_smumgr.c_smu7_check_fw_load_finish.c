#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
struct smu7_smumgr {scalar_t__ soft_regs_start; } ;
struct pp_hwmgr {scalar_t__ smu_backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMU_SoftRegisters ; 
 int /*<<< orphan*/  UcodeLoadStatus ; 
 int /*<<< orphan*/  mmSMC_IND_INDEX_11 ; 
 int phm_wait_on_indirect_register (struct pp_hwmgr*,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 scalar_t__ smum_get_offsetof (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int smu7_check_fw_load_finish(struct pp_hwmgr *hwmgr, uint32_t fw_type)
{
	struct smu7_smumgr *smu_data = (struct smu7_smumgr *)(hwmgr->smu_backend);
	uint32_t ret;

	ret = phm_wait_on_indirect_register(hwmgr, mmSMC_IND_INDEX_11,
					smu_data->soft_regs_start + smum_get_offsetof(hwmgr,
					SMU_SoftRegisters, UcodeLoadStatus),
					fw_type, fw_type);
	return ret;
}