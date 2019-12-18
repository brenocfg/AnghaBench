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
struct pp_hwmgr {scalar_t__ chip_id; int feature_mask; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGS_IND_REG__SMC ; 
 scalar_t__ CHIP_VEGAM ; 
 int /*<<< orphan*/  PHM_WRITE_VFPF_INDIRECT_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPSMC_MSG_Voltage_Cntl_Enable ; 
 int PP_SMC_VOLTAGE_CONTROL_MASK ; 
 int /*<<< orphan*/  PSI0_EN ; 
 int /*<<< orphan*/  PSI1 ; 
 int /*<<< orphan*/  PWR_SVI2_PLANE1_LOAD ; 
 int /*<<< orphan*/  smum_send_msg_to_smc (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu7_enable_smc_voltage_controller(struct pp_hwmgr *hwmgr)
{
	if (hwmgr->chip_id == CHIP_VEGAM) {
		PHM_WRITE_VFPF_INDIRECT_FIELD(hwmgr->device,
				CGS_IND_REG__SMC, PWR_SVI2_PLANE1_LOAD, PSI1, 0);
		PHM_WRITE_VFPF_INDIRECT_FIELD(hwmgr->device,
				CGS_IND_REG__SMC, PWR_SVI2_PLANE1_LOAD, PSI0_EN, 0);
	}

	if (hwmgr->feature_mask & PP_SMC_VOLTAGE_CONTROL_MASK)
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_Voltage_Cntl_Enable);

	return 0;
}