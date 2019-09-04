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
 int /*<<< orphan*/  kv_dpm_powergate_acp (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  kv_dpm_powergate_samu (struct amdgpu_device*,int) ; 

__attribute__((used)) static int kv_dpm_late_init(void *handle)
{
	/* powerdown unused blocks for now */
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	if (!adev->pm.dpm_enabled)
		return 0;

	kv_dpm_powergate_acp(adev, true);
	kv_dpm_powergate_samu(adev, true);

	return 0;
}