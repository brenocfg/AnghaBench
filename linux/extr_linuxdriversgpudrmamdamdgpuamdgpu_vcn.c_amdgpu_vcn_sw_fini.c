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
struct TYPE_2__ {int num_enc_rings; int /*<<< orphan*/  fw; int /*<<< orphan*/  ring_jpeg; int /*<<< orphan*/ * ring_enc; int /*<<< orphan*/  ring_dec; int /*<<< orphan*/  cpu_addr; int /*<<< orphan*/  gpu_addr; int /*<<< orphan*/  vcpu_bo; int /*<<< orphan*/  saved_bo; } ;
struct amdgpu_device {TYPE_1__ vcn; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  amdgpu_ring_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 

int amdgpu_vcn_sw_fini(struct amdgpu_device *adev)
{
	int i;

	kvfree(adev->vcn.saved_bo);

	amdgpu_bo_free_kernel(&adev->vcn.vcpu_bo,
			      &adev->vcn.gpu_addr,
			      (void **)&adev->vcn.cpu_addr);

	amdgpu_ring_fini(&adev->vcn.ring_dec);

	for (i = 0; i < adev->vcn.num_enc_rings; ++i)
		amdgpu_ring_fini(&adev->vcn.ring_enc[i]);

	amdgpu_ring_fini(&adev->vcn.ring_jpeg);

	release_firmware(adev->vcn.fw);

	return 0;
}