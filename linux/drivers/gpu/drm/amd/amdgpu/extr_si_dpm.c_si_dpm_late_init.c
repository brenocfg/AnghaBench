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
struct TYPE_2__ {int /*<<< orphan*/  dpm_enabled; } ;
struct amdgpu_device {TYPE_1__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  si_dpm_powergate_uvd (struct amdgpu_device*,int) ; 
 int si_set_temperature_range (struct amdgpu_device*) ; 

__attribute__((used)) static int si_dpm_late_init(void *handle)
{
	int ret;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	if (!adev->pm.dpm_enabled)
		return 0;

	ret = si_set_temperature_range(adev);
	if (ret)
		return ret;
#if 0 //TODO ?
	si_dpm_powergate_uvd(adev, true);
#endif
	return 0;
}