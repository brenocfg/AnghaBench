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
struct smu_context {int /*<<< orphan*/  mutex; } ;
struct amdgpu_device {struct smu_context smu; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int smu_smc_table_hw_init (struct smu_context*,int) ; 
 int smu_start_thermal_control (struct smu_context*) ; 

__attribute__((used)) static int smu_resume(void *handle)
{
	int ret;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct smu_context *smu = &adev->smu;

	pr_info("SMU is resuming...\n");

	mutex_lock(&smu->mutex);

	ret = smu_smc_table_hw_init(smu, false);
	if (ret)
		goto failed;

	ret = smu_start_thermal_control(smu);
	if (ret)
		goto failed;

	mutex_unlock(&smu->mutex);

	pr_info("SMU is resumed successfully!\n");

	return 0;
failed:
	mutex_unlock(&smu->mutex);
	return ret;
}