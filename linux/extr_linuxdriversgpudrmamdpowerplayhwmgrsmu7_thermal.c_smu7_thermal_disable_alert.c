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
struct pp_hwmgr {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGS_IND_REG__SMC ; 
 int /*<<< orphan*/  CG_THERMAL_INT ; 
 int PHM_READ_VFPF_INDIRECT_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHM_WRITE_VFPF_INDIRECT_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PPSMC_MSG_Thermal_Cntl_Disable ; 
 int SMU7_THERMAL_HIGH_ALERT_MASK ; 
 int SMU7_THERMAL_LOW_ALERT_MASK ; 
 int /*<<< orphan*/  THERM_INT_MASK ; 
 int smum_send_msg_to_smc (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

int smu7_thermal_disable_alert(struct pp_hwmgr *hwmgr)
{
	uint32_t alert;

	alert = PHM_READ_VFPF_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_THERMAL_INT, THERM_INT_MASK);
	alert |= (SMU7_THERMAL_HIGH_ALERT_MASK | SMU7_THERMAL_LOW_ALERT_MASK);
	PHM_WRITE_VFPF_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_THERMAL_INT, THERM_INT_MASK, alert);

	/* send message to SMU to disable internal thermal interrupts */
	return smum_send_msg_to_smc(hwmgr, PPSMC_MSG_Thermal_Cntl_Disable);
}