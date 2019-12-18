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
typedef  scalar_t__ uint32_t ;
struct pp_hwmgr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_GetDriverIfVersion ; 
 scalar_t__ SMU10_DRIVER_IF_VERSION ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ smu10_read_arg_from_smc (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu10_send_msg_to_smc (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu10_verify_smc_interface(struct pp_hwmgr *hwmgr)
{
	uint32_t smc_driver_if_version;

	smu10_send_msg_to_smc(hwmgr,
			PPSMC_MSG_GetDriverIfVersion);
	smc_driver_if_version = smu10_read_arg_from_smc(hwmgr);

	if ((smc_driver_if_version != SMU10_DRIVER_IF_VERSION) &&
	    (smc_driver_if_version != SMU10_DRIVER_IF_VERSION + 1)) {
		pr_err("Attempt to read SMC IF Version Number Failed!\n");
		return -EINVAL;
	}

	return 0;
}