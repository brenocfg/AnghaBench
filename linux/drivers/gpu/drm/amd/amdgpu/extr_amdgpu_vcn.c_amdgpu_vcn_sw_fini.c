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
struct TYPE_4__ {int num_vcn_inst; int harvest_config; int num_enc_rings; int /*<<< orphan*/  fw; TYPE_1__* inst; int /*<<< orphan*/  dpg_sram_cpu_addr; int /*<<< orphan*/  dpg_sram_gpu_addr; int /*<<< orphan*/  dpg_sram_bo; scalar_t__ indirect_sram; } ;
struct amdgpu_device {TYPE_2__ vcn; } ;
struct TYPE_3__ {int /*<<< orphan*/  ring_jpeg; int /*<<< orphan*/ * ring_enc; int /*<<< orphan*/  ring_dec; int /*<<< orphan*/  cpu_addr; int /*<<< orphan*/  gpu_addr; int /*<<< orphan*/  vcpu_bo; int /*<<< orphan*/  saved_bo; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  amdgpu_ring_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 

int amdgpu_vcn_sw_fini(struct amdgpu_device *adev)
{
	int i, j;

	if (adev->vcn.indirect_sram) {
		amdgpu_bo_free_kernel(&adev->vcn.dpg_sram_bo,
				      &adev->vcn.dpg_sram_gpu_addr,
				      (void **)&adev->vcn.dpg_sram_cpu_addr);
	}

	for (j = 0; j < adev->vcn.num_vcn_inst; ++j) {
		if (adev->vcn.harvest_config & (1 << j))
			continue;
		kvfree(adev->vcn.inst[j].saved_bo);

		amdgpu_bo_free_kernel(&adev->vcn.inst[j].vcpu_bo,
					  &adev->vcn.inst[j].gpu_addr,
					  (void **)&adev->vcn.inst[j].cpu_addr);

		amdgpu_ring_fini(&adev->vcn.inst[j].ring_dec);

		for (i = 0; i < adev->vcn.num_enc_rings; ++i)
			amdgpu_ring_fini(&adev->vcn.inst[j].ring_enc[i]);

		amdgpu_ring_fini(&adev->vcn.inst[j].ring_jpeg);
	}

	release_firmware(adev->vcn.fw);

	return 0;
}