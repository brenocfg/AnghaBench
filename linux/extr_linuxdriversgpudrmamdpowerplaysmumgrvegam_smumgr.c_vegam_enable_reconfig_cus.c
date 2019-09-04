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
struct pp_hwmgr {struct amdgpu_device* adev; } ;
struct TYPE_3__ {int /*<<< orphan*/  number; } ;
struct TYPE_4__ {TYPE_1__ cu_info; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_EnableModeSwitchRLCNotification ; 
 int /*<<< orphan*/  smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vegam_enable_reconfig_cus(struct pp_hwmgr *hwmgr)
{
	struct amdgpu_device *adev = hwmgr->adev;

	smum_send_msg_to_smc_with_parameter(hwmgr,
					    PPSMC_MSG_EnableModeSwitchRLCNotification,
					    adev->gfx.cu_info.number);

	return 0;
}