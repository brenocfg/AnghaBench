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
struct TYPE_2__ {int /*<<< orphan*/  srbm_soft_reset; } ;
struct amdgpu_device {int /*<<< orphan*/  dev; TYPE_1__ gmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gmc_v8_0_mc_stop (struct amdgpu_device*) ; 
 scalar_t__ gmc_v8_0_wait_for_idle (struct amdgpu_device*) ; 

__attribute__((used)) static int gmc_v8_0_pre_soft_reset(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	if (!adev->gmc.srbm_soft_reset)
		return 0;

	gmc_v8_0_mc_stop(adev);
	if (gmc_v8_0_wait_for_idle(adev)) {
		dev_warn(adev->dev, "Wait for GMC idle timed out !\n");
	}

	return 0;
}