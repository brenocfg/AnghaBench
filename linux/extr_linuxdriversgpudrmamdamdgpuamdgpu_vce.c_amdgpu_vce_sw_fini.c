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
struct TYPE_2__ {unsigned int num_rings; int /*<<< orphan*/  idle_mutex; int /*<<< orphan*/  fw; int /*<<< orphan*/ * ring; int /*<<< orphan*/  cpu_addr; int /*<<< orphan*/  gpu_addr; int /*<<< orphan*/ * vcpu_bo; int /*<<< orphan*/  entity; } ;
struct amdgpu_device {TYPE_1__ vce; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  amdgpu_ring_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_sched_entity_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 

int amdgpu_vce_sw_fini(struct amdgpu_device *adev)
{
	unsigned i;

	if (adev->vce.vcpu_bo == NULL)
		return 0;

	drm_sched_entity_destroy(&adev->vce.entity);

	amdgpu_bo_free_kernel(&adev->vce.vcpu_bo, &adev->vce.gpu_addr,
		(void **)&adev->vce.cpu_addr);

	for (i = 0; i < adev->vce.num_rings; i++)
		amdgpu_ring_fini(&adev->vce.ring[i]);

	release_firmware(adev->vce.fw);
	mutex_destroy(&adev->vce.idle_mutex);

	return 0;
}