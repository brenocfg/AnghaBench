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
typedef  scalar_t__ uint32_t ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DramReady ; 
 int /*<<< orphan*/  EccDis ; 
 scalar_t__ REG_GET_FIELD (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  RdEccEn ; 
 int /*<<< orphan*/  UMCCH0_0_EccCtrl ; 
 int /*<<< orphan*/  UMCCH0_0_UMC_CONFIG ; 
 int /*<<< orphan*/  UMCCH0_0_UmcLocalCap ; 
 int /*<<< orphan*/  WrEccEn ; 
 scalar_t__* ecc_umcch_eccctrl_addrs ; 
 scalar_t__* ecc_umcch_umc_config_addrs ; 
 scalar_t__* ecc_umclocalcap_addrs ; 

__attribute__((used)) static int gmc_v9_0_ecc_available(struct amdgpu_device *adev)
{
	uint32_t reg_val;
	uint32_t reg_addr;
	uint32_t field_val;
	size_t i;
	uint32_t fv2;
	size_t lost_sheep;

	DRM_DEBUG("ecc: gmc_v9_0_ecc_available()\n");

	lost_sheep = 0;
	for (i = 0; i < ARRAY_SIZE(ecc_umclocalcap_addrs); ++i) {
		reg_addr = ecc_umclocalcap_addrs[i];
		DRM_DEBUG("ecc: "
			  "UMCCH_UmcLocalCap[%zu]: reg_addr: 0x%08x\n",
			  i, reg_addr);
		reg_val = RREG32(reg_addr);
		field_val = REG_GET_FIELD(reg_val, UMCCH0_0_UmcLocalCap,
					  EccDis);
		DRM_DEBUG("ecc: "
			  "reg_val: 0x%08x, "
			  "EccDis: 0x%08x, ",
			  reg_val, field_val);
		if (field_val) {
			DRM_ERROR("ecc: UmcLocalCap:EccDis is set.\n");
			++lost_sheep;
		}
	}

	for (i = 0; i < ARRAY_SIZE(ecc_umcch_umc_config_addrs); ++i) {
		reg_addr = ecc_umcch_umc_config_addrs[i];
		DRM_DEBUG("ecc: "
			  "UMCCH0_0_UMC_CONFIG[%zu]: reg_addr: 0x%08x",
			  i, reg_addr);
		reg_val = RREG32(reg_addr);
		field_val = REG_GET_FIELD(reg_val, UMCCH0_0_UMC_CONFIG,
					  DramReady);
		DRM_DEBUG("ecc: "
			  "reg_val: 0x%08x, "
			  "DramReady: 0x%08x\n",
			  reg_val, field_val);

		if (!field_val) {
			DRM_ERROR("ecc: UMC_CONFIG:DramReady is not set.\n");
			++lost_sheep;
		}
	}

	for (i = 0; i < ARRAY_SIZE(ecc_umcch_eccctrl_addrs); ++i) {
		reg_addr = ecc_umcch_eccctrl_addrs[i];
		DRM_DEBUG("ecc: "
			  "UMCCH_EccCtrl[%zu]: reg_addr: 0x%08x, ",
			  i, reg_addr);
		reg_val = RREG32(reg_addr);
		field_val = REG_GET_FIELD(reg_val, UMCCH0_0_EccCtrl,
					  WrEccEn);
		fv2 = REG_GET_FIELD(reg_val, UMCCH0_0_EccCtrl,
				    RdEccEn);
		DRM_DEBUG("ecc: "
			  "reg_val: 0x%08x, "
			  "WrEccEn: 0x%08x, "
			  "RdEccEn: 0x%08x\n",
			  reg_val, field_val, fv2);

		if (!field_val) {
			DRM_DEBUG("ecc: WrEccEn is not set\n");
			++lost_sheep;
		}
		if (!fv2) {
			DRM_DEBUG("ecc: RdEccEn is not set\n");
			++lost_sheep;
		}
	}

	DRM_DEBUG("ecc: lost_sheep: %zu\n", lost_sheep);
	return lost_sheep == 0;
}