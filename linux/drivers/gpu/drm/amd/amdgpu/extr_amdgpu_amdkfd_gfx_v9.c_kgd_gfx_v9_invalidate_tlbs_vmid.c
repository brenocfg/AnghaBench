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
typedef  int /*<<< orphan*/  uint16_t ;
struct kgd_dev {int dummy; } ;
struct amdgpu_device {int num_vmhubs; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_amdkfd_is_kfd_vmid (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_gmc_flush_gpu_tlb (struct amdgpu_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

int kgd_gfx_v9_invalidate_tlbs_vmid(struct kgd_dev *kgd, uint16_t vmid)
{
	struct amdgpu_device *adev = (struct amdgpu_device *) kgd;
	int i;

	if (!amdgpu_amdkfd_is_kfd_vmid(adev, vmid)) {
		pr_err("non kfd vmid %d\n", vmid);
		return 0;
	}

	/* Use legacy mode tlb invalidation.
	 *
	 * Currently on Raven the code below is broken for anything but
	 * legacy mode due to a MMHUB power gating problem. A workaround
	 * is for MMHUB to wait until the condition PER_VMID_INVALIDATE_REQ
	 * == PER_VMID_INVALIDATE_ACK instead of simply waiting for the ack
	 * bit.
	 *
	 * TODO 1: agree on the right set of invalidation registers for
	 * KFD use. Use the last one for now. Invalidate both GC and
	 * MMHUB.
	 *
	 * TODO 2: support range-based invalidation, requires kfg2kgd
	 * interface change
	 */
	for (i = 0; i < adev->num_vmhubs; i++)
		amdgpu_gmc_flush_gpu_tlb(adev, vmid, i, 0);

	return 0;
}