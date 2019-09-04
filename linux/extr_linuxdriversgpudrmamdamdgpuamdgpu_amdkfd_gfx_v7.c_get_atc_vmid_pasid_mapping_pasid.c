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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct kgd_dev {int dummy; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int ATC_VMID0_PASID_MAPPING__PASID_MASK ; 
 int RREG32 (scalar_t__) ; 
 scalar_t__ mmATC_VMID0_PASID_MAPPING ; 

__attribute__((used)) static uint16_t get_atc_vmid_pasid_mapping_pasid(struct kgd_dev *kgd,
								uint8_t vmid)
{
	uint32_t reg;
	struct amdgpu_device *adev = (struct amdgpu_device *) kgd;

	reg = RREG32(mmATC_VMID0_PASID_MAPPING + vmid);
	return reg & ATC_VMID0_PASID_MAPPING__PASID_MASK;
}