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
typedef  int uint16_t ;
struct kgd_dev {int dummy; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amdgpu_amdkfd_is_kfd_vmid (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  mmVM_INVALIDATE_REQUEST ; 
 int /*<<< orphan*/  mmVM_INVALIDATE_RESPONSE ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int invalidate_tlbs_vmid(struct kgd_dev *kgd, uint16_t vmid)
{
	struct amdgpu_device *adev = (struct amdgpu_device *) kgd;

	if (!amdgpu_amdkfd_is_kfd_vmid(adev, vmid)) {
		pr_err("non kfd vmid\n");
		return 0;
	}

	WREG32(mmVM_INVALIDATE_REQUEST, 1 << vmid);
	RREG32(mmVM_INVALIDATE_RESPONSE);
	return 0;
}