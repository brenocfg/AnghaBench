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
struct kgd_dev {int dummy; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int ATC_VMID0_PASID_MAPPING__VALID_MASK ; 
 int /*<<< orphan*/  ATHUB ; 
 int RREG32 (scalar_t__) ; 
 scalar_t__ SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmATC_VMID0_PASID_MAPPING ; 

__attribute__((used)) static bool get_atc_vmid_pasid_mapping_valid(struct kgd_dev *kgd,
							uint8_t vmid)
{
	uint32_t reg;
	struct amdgpu_device *adev = (struct amdgpu_device *) kgd;

	reg = RREG32(SOC15_REG_OFFSET(ATHUB, 0, mmATC_VMID0_PASID_MAPPING)
		     + vmid);
	return reg & ATC_VMID0_PASID_MAPPING__VALID_MASK;
}