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
struct psp_context {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct amdgpu_device {TYPE_1__ firmware; struct psp_context psp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int psp_hw_start (struct psp_context*) ; 
 int psp_np_fw_load (struct psp_context*) ; 

__attribute__((used)) static int psp_resume(void *handle)
{
	int ret;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct psp_context *psp = &adev->psp;

	DRM_INFO("PSP is resuming...\n");

	mutex_lock(&adev->firmware.mutex);

	ret = psp_hw_start(psp);
	if (ret)
		goto failed;

	ret = psp_np_fw_load(psp);
	if (ret)
		goto failed;

	mutex_unlock(&adev->firmware.mutex);

	return 0;

failed:
	DRM_ERROR("PSP resume failed\n");
	mutex_unlock(&adev->firmware.mutex);
	return ret;
}