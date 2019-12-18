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
struct TYPE_2__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  load_type; } ;
struct amdgpu_device {TYPE_1__ firmware; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_FW_LOAD_DIRECT ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int amdgpu_ucode_init_bo (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int psp_load_fw (struct amdgpu_device*) ; 

__attribute__((used)) static int psp_hw_init(void *handle)
{
	int ret;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	mutex_lock(&adev->firmware.mutex);
	/*
	 * This sequence is just used on hw_init only once, no need on
	 * resume.
	 */
	ret = amdgpu_ucode_init_bo(adev);
	if (ret)
		goto failed;

	ret = psp_load_fw(adev);
	if (ret) {
		DRM_ERROR("PSP firmware loading failed\n");
		goto failed;
	}

	mutex_unlock(&adev->firmware.mutex);
	return 0;

failed:
	adev->firmware.load_type = AMDGPU_FW_LOAD_DIRECT;
	mutex_unlock(&adev->firmware.mutex);
	return -EINVAL;
}