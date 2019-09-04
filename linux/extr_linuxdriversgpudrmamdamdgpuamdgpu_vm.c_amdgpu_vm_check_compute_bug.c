#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct amdgpu_ring {int has_compute_vm_bug; TYPE_3__* funcs; } ;
struct amdgpu_ip_block {TYPE_1__* version; } ;
struct TYPE_5__ {int mec_fw_version; } ;
struct amdgpu_device {int num_rings; struct amdgpu_ring** rings; TYPE_2__ gfx; } ;
struct TYPE_6__ {scalar_t__ type; } ;
struct TYPE_4__ {int major; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_RING_TYPE_COMPUTE ; 
 int /*<<< orphan*/  AMD_IP_BLOCK_TYPE_GFX ; 
 struct amdgpu_ip_block* amdgpu_device_ip_get_ip_block (struct amdgpu_device*,int /*<<< orphan*/ ) ; 

void amdgpu_vm_check_compute_bug(struct amdgpu_device *adev)
{
	const struct amdgpu_ip_block *ip_block;
	bool has_compute_vm_bug;
	struct amdgpu_ring *ring;
	int i;

	has_compute_vm_bug = false;

	ip_block = amdgpu_device_ip_get_ip_block(adev, AMD_IP_BLOCK_TYPE_GFX);
	if (ip_block) {
		/* Compute has a VM bug for GFX version < 7.
		   Compute has a VM bug for GFX 8 MEC firmware version < 673.*/
		if (ip_block->version->major <= 7)
			has_compute_vm_bug = true;
		else if (ip_block->version->major == 8)
			if (adev->gfx.mec_fw_version < 673)
				has_compute_vm_bug = true;
	}

	for (i = 0; i < adev->num_rings; i++) {
		ring = adev->rings[i];
		if (ring->funcs->type == AMDGPU_RING_TYPE_COMPUTE)
			/* only compute rings */
			ring->has_compute_vm_bug = has_compute_vm_bug;
		else
			ring->has_compute_vm_bug = false;
	}
}