#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int num_uvd_inst; int harvest_config; int /*<<< orphan*/  fw; TYPE_1__* inst; int /*<<< orphan*/  entity; } ;
struct amdgpu_device {TYPE_2__ uvd; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ring_enc; int /*<<< orphan*/  ring; int /*<<< orphan*/  cpu_addr; int /*<<< orphan*/  gpu_addr; int /*<<< orphan*/  vcpu_bo; int /*<<< orphan*/  saved_bo; } ;

/* Variables and functions */
 int AMDGPU_MAX_UVD_ENC_RINGS ; 
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  amdgpu_ring_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_sched_entity_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 

int amdgpu_uvd_sw_fini(struct amdgpu_device *adev)
{
	int i, j;

	drm_sched_entity_destroy(&adev->uvd.entity);

	for (j = 0; j < adev->uvd.num_uvd_inst; ++j) {
		if (adev->uvd.harvest_config & (1 << j))
			continue;
		kvfree(adev->uvd.inst[j].saved_bo);

		amdgpu_bo_free_kernel(&adev->uvd.inst[j].vcpu_bo,
				      &adev->uvd.inst[j].gpu_addr,
				      (void **)&adev->uvd.inst[j].cpu_addr);

		amdgpu_ring_fini(&adev->uvd.inst[j].ring);

		for (i = 0; i < AMDGPU_MAX_UVD_ENC_RINGS; ++i)
			amdgpu_ring_fini(&adev->uvd.inst[j].ring_enc[i]);
	}
	release_firmware(adev->uvd.fw);

	return 0;
}