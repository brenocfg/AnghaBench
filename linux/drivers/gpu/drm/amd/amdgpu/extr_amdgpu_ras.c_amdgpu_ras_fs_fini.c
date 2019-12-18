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
 int /*<<< orphan*/  amdgpu_ras_debugfs_remove_all (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_ras_sysfs_remove_all (struct amdgpu_device*) ; 

__attribute__((used)) static int amdgpu_ras_fs_fini(struct amdgpu_device *adev)
{
	amdgpu_ras_debugfs_remove_all(adev);
	amdgpu_ras_sysfs_remove_all(adev);
	return 0;
}