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
typedef  int /*<<< orphan*/  uint16_t ;
struct kgd_dev {int dummy; } ;
struct amdgpu_ring {scalar_t__ ready; } ;
struct TYPE_3__ {struct amdgpu_ring ring; } ;
struct TYPE_4__ {TYPE_1__ kiq; } ;
struct amdgpu_device {scalar_t__ in_gpu_reset; TYPE_2__ gfx; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  amdgpu_amdkfd_is_kfd_vmid (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  get_atc_vmid_pasid_mapping_pasid (struct kgd_dev*,int) ; 
 scalar_t__ get_atc_vmid_pasid_mapping_valid (struct kgd_dev*,int) ; 
 int invalidate_tlbs_with_kiq (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_vmid_invalidate_request (struct kgd_dev*,int) ; 

__attribute__((used)) static int invalidate_tlbs(struct kgd_dev *kgd, uint16_t pasid)
{
	struct amdgpu_device *adev = (struct amdgpu_device *) kgd;
	int vmid;
	struct amdgpu_ring *ring = &adev->gfx.kiq.ring;

	if (adev->in_gpu_reset)
		return -EIO;

	if (ring->ready)
		return invalidate_tlbs_with_kiq(adev, pasid);

	for (vmid = 0; vmid < 16; vmid++) {
		if (!amdgpu_amdkfd_is_kfd_vmid(adev, vmid))
			continue;
		if (get_atc_vmid_pasid_mapping_valid(kgd, vmid)) {
			if (get_atc_vmid_pasid_mapping_pasid(kgd, vmid)
				== pasid) {
				write_vmid_invalidate_request(kgd, vmid);
				break;
			}
		}
	}

	return 0;
}