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
struct amdgpu_device {TYPE_1__ vce; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdelay (int) ; 
 int vce_v3_0_suspend (struct amdgpu_device*) ; 

__attribute__((used)) static int vce_v3_0_pre_soft_reset(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	if (!adev->vce.srbm_soft_reset)
		return 0;

	mdelay(5);

	return vce_v3_0_suspend(adev);
}