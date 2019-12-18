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
struct smu_context {int pm_enabled; int /*<<< orphan*/  mutex; struct amdgpu_device* adev; } ;
struct amdgpu_device {struct smu_context smu; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_dpm ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int smu_set_funcs (struct amdgpu_device*) ; 

__attribute__((used)) static int smu_early_init(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct smu_context *smu = &adev->smu;

	smu->adev = adev;
	smu->pm_enabled = !!amdgpu_dpm;
	mutex_init(&smu->mutex);

	return smu_set_funcs(adev);
}