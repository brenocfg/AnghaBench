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
struct pp_hwmgr {int smu_version; struct amdgpu_device* adev; } ;
struct TYPE_2__ {int fw_version; } ;
struct amdgpu_device {TYPE_1__ pm; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_GetSmuVersion ; 
 int smu10_read_arg_from_smc (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu10_smc_enable_sdma (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu10_smc_enable_vcn (struct pp_hwmgr*) ; 
 scalar_t__ smu10_verify_smc_interface (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smum_send_msg_to_smc (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu10_start_smu(struct pp_hwmgr *hwmgr)
{
	struct amdgpu_device *adev = hwmgr->adev;

	smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetSmuVersion);
	hwmgr->smu_version = smu10_read_arg_from_smc(hwmgr);
	adev->pm.fw_version = hwmgr->smu_version >> 8;

	if (smu10_verify_smc_interface(hwmgr))
		return -EINVAL;
	smu10_smc_enable_sdma(hwmgr);
	smu10_smc_enable_vcn(hwmgr);
	return 0;
}