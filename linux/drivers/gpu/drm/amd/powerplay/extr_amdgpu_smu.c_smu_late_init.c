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
struct TYPE_2__ {int /*<<< orphan*/  dpm_level; } ;
struct smu_context {int /*<<< orphan*/  mutex; TYPE_1__ smu_dpm; int /*<<< orphan*/  pm_enabled; } ;
struct amdgpu_device {struct smu_context smu; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_PP_TASK_COMPLETE_INIT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smu_handle_task (struct smu_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu_late_init(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct smu_context *smu = &adev->smu;

	if (!smu->pm_enabled)
		return 0;

	mutex_lock(&smu->mutex);
	smu_handle_task(&adev->smu,
			smu->smu_dpm.dpm_level,
			AMD_PP_TASK_COMPLETE_INIT);
	mutex_unlock(&smu->mutex);

	return 0;
}