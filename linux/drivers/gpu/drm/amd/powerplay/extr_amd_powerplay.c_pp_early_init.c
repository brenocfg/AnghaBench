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
struct TYPE_2__ {int /*<<< orphan*/  pp_handle; } ;
struct amdgpu_device {TYPE_1__ powerplay; } ;

/* Variables and functions */
 int EINVAL ; 
 int amd_powerplay_create (struct amdgpu_device*) ; 
 int hwmgr_early_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pp_early_init(void *handle)
{
	int ret;
	struct amdgpu_device *adev = handle;

	ret = amd_powerplay_create(adev);

	if (ret != 0)
		return ret;

	ret = hwmgr_early_init(adev->powerplay.pp_handle);
	if (ret)
		return -EINVAL;

	return 0;
}