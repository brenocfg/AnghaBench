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
typedef  scalar_t__ u32 ;
struct pp_hwmgr {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGS_IND_REG__SMC ; 
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_GetCurrPkgPwr ; 
 int /*<<< orphan*/  PPSMC_MSG_PmStatusLogSample ; 
 int /*<<< orphan*/  PPSMC_MSG_PmStatusLogStart ; 
 scalar_t__ cgs_read_ind_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cgs_read_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgs_write_ind_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixSMU_PM_STATUS_95 ; 
 int /*<<< orphan*/  mmSMC_MSG_ARG_0 ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  smum_send_msg_to_smc (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu7_get_gpu_power(struct pp_hwmgr *hwmgr, u32 *query)
{
	int i;
	u32 tmp = 0;

	if (!query)
		return -EINVAL;

	smum_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_GetCurrPkgPwr, 0);
	tmp = cgs_read_register(hwmgr->device, mmSMC_MSG_ARG_0);
	*query = tmp;

	if (tmp != 0)
		return 0;

	smum_send_msg_to_smc(hwmgr, PPSMC_MSG_PmStatusLogStart);
	cgs_write_ind_register(hwmgr->device, CGS_IND_REG__SMC,
							ixSMU_PM_STATUS_95, 0);

	for (i = 0; i < 10; i++) {
		msleep(500);
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_PmStatusLogSample);
		tmp = cgs_read_ind_register(hwmgr->device,
						CGS_IND_REG__SMC,
						ixSMU_PM_STATUS_95);
		if (tmp != 0)
			break;
	}
	*query = tmp;

	return 0;
}