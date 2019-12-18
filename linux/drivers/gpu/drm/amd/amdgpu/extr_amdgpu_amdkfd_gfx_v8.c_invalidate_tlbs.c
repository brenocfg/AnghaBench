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
typedef  unsigned int uint16_t ;
struct kgd_dev {int dummy; } ;
struct amdgpu_device {scalar_t__ in_gpu_reset; } ;

/* Variables and functions */
 unsigned int ATC_VMID0_PASID_MAPPING__PASID_MASK ; 
 unsigned int ATC_VMID0_PASID_MAPPING__VALID_MASK ; 
 int EIO ; 
 unsigned int RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amdgpu_amdkfd_is_kfd_vmid (struct amdgpu_device*,int) ; 
 scalar_t__ mmATC_VMID0_PASID_MAPPING ; 
 int /*<<< orphan*/  mmVM_INVALIDATE_REQUEST ; 
 scalar_t__ mmVM_INVALIDATE_RESPONSE ; 

__attribute__((used)) static int invalidate_tlbs(struct kgd_dev *kgd, uint16_t pasid)
{
	struct amdgpu_device *adev = (struct amdgpu_device *) kgd;
	int vmid;
	unsigned int tmp;

	if (adev->in_gpu_reset)
		return -EIO;

	for (vmid = 0; vmid < 16; vmid++) {
		if (!amdgpu_amdkfd_is_kfd_vmid(adev, vmid))
			continue;

		tmp = RREG32(mmATC_VMID0_PASID_MAPPING + vmid);
		if ((tmp & ATC_VMID0_PASID_MAPPING__VALID_MASK) &&
			(tmp & ATC_VMID0_PASID_MAPPING__PASID_MASK) == pasid) {
			WREG32(mmVM_INVALIDATE_REQUEST, 1 << vmid);
			RREG32(mmVM_INVALIDATE_RESPONSE);
			break;
		}
	}

	return 0;
}