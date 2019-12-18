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
typedef  unsigned int uint32_t ;
struct kgd_dev {int dummy; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 unsigned int ATC_VMID0_PASID_MAPPING__VALID_MASK ; 
 int /*<<< orphan*/  ATHUB ; 
 int /*<<< orphan*/  OSSSYS ; 
 unsigned int RREG32 (scalar_t__) ; 
 scalar_t__ SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 struct amdgpu_device* get_amdgpu_device (struct kgd_dev*) ; 
 int /*<<< orphan*/  mmATC_VMID0_PASID_MAPPING ; 
 int /*<<< orphan*/  mmATC_VMID16_PASID_MAPPING ; 
 int /*<<< orphan*/  mmATC_VMID_PASID_MAPPING_UPDATE_STATUS ; 
 int /*<<< orphan*/  mmIH_VMID_0_LUT ; 
 int /*<<< orphan*/  mmIH_VMID_0_LUT_MM ; 

int kgd_gfx_v9_set_pasid_vmid_mapping(struct kgd_dev *kgd, unsigned int pasid,
					unsigned int vmid)
{
	struct amdgpu_device *adev = get_amdgpu_device(kgd);

	/*
	 * We have to assume that there is no outstanding mapping.
	 * The ATC_VMID_PASID_MAPPING_UPDATE_STATUS bit could be 0 because
	 * a mapping is in progress or because a mapping finished
	 * and the SW cleared it.
	 * So the protocol is to always wait & clear.
	 */
	uint32_t pasid_mapping = (pasid == 0) ? 0 : (uint32_t)pasid |
			ATC_VMID0_PASID_MAPPING__VALID_MASK;

	/*
	 * need to do this twice, once for gfx and once for mmhub
	 * for ATC add 16 to VMID for mmhub, for IH different registers.
	 * ATC_VMID0..15 registers are separate from ATC_VMID16..31.
	 */

	WREG32(SOC15_REG_OFFSET(ATHUB, 0, mmATC_VMID0_PASID_MAPPING) + vmid,
	       pasid_mapping);

	while (!(RREG32(SOC15_REG_OFFSET(
				ATHUB, 0,
				mmATC_VMID_PASID_MAPPING_UPDATE_STATUS)) &
		 (1U << vmid)))
		cpu_relax();

	WREG32(SOC15_REG_OFFSET(ATHUB, 0,
				mmATC_VMID_PASID_MAPPING_UPDATE_STATUS),
	       1U << vmid);

	/* Mapping vmid to pasid also for IH block */
	WREG32(SOC15_REG_OFFSET(OSSSYS, 0, mmIH_VMID_0_LUT) + vmid,
	       pasid_mapping);

	WREG32(SOC15_REG_OFFSET(ATHUB, 0, mmATC_VMID16_PASID_MAPPING) + vmid,
	       pasid_mapping);

	while (!(RREG32(SOC15_REG_OFFSET(
				ATHUB, 0,
				mmATC_VMID_PASID_MAPPING_UPDATE_STATUS)) &
		 (1U << (vmid + 16))))
		cpu_relax();

	WREG32(SOC15_REG_OFFSET(ATHUB, 0,
				mmATC_VMID_PASID_MAPPING_UPDATE_STATUS),
	       1U << (vmid + 16));

	/* Mapping vmid to pasid also for IH block */
	WREG32(SOC15_REG_OFFSET(OSSSYS, 0, mmIH_VMID_0_LUT_MM) + vmid,
	       pasid_mapping);
	return 0;
}