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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */

int amdgpu_debugfs_fence_init(struct amdgpu_device *adev)
{
#if defined(CONFIG_DEBUG_FS)
	if (amdgpu_sriov_vf(adev))
		return amdgpu_debugfs_add_files(adev, amdgpu_debugfs_fence_list_sriov, 1);
	return amdgpu_debugfs_add_files(adev, amdgpu_debugfs_fence_list, 2);
#else
	return 0;
#endif
}