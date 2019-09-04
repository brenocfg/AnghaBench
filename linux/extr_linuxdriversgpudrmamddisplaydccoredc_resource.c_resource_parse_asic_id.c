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
struct hw_asic_id {int chip_family; int /*<<< orphan*/  hw_internal_rev; } ;
typedef  enum dce_version { ____Placeholder_dce_version } dce_version ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_REV_IS_BHAVANI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASIC_REV_IS_FIJI_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASIC_REV_IS_GODAVARI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASIC_REV_IS_KALINDI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASIC_REV_IS_POLARIS10_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASIC_REV_IS_POLARIS11_M (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASIC_REV_IS_POLARIS12_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASIC_REV_IS_TONGA_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASIC_REV_IS_VEGAM (int /*<<< orphan*/ ) ; 
 int DCE_VERSION_10_0 ; 
 int DCE_VERSION_11_0 ; 
 int DCE_VERSION_11_2 ; 
 int DCE_VERSION_11_22 ; 
 int DCE_VERSION_12_0 ; 
 int DCE_VERSION_8_0 ; 
 int DCE_VERSION_8_1 ; 
 int DCE_VERSION_8_3 ; 
 int DCE_VERSION_UNKNOWN ; 
#define  FAMILY_AI 132 
#define  FAMILY_CI 131 
#define  FAMILY_CZ 130 
#define  FAMILY_KV 129 
#define  FAMILY_VI 128 

enum dce_version resource_parse_asic_id(struct hw_asic_id asic_id)
{
	enum dce_version dc_version = DCE_VERSION_UNKNOWN;
	switch (asic_id.chip_family) {

	case FAMILY_CI:
		dc_version = DCE_VERSION_8_0;
		break;
	case FAMILY_KV:
		if (ASIC_REV_IS_KALINDI(asic_id.hw_internal_rev) ||
		    ASIC_REV_IS_BHAVANI(asic_id.hw_internal_rev) ||
		    ASIC_REV_IS_GODAVARI(asic_id.hw_internal_rev))
			dc_version = DCE_VERSION_8_3;
		else
			dc_version = DCE_VERSION_8_1;
		break;
	case FAMILY_CZ:
		dc_version = DCE_VERSION_11_0;
		break;

	case FAMILY_VI:
		if (ASIC_REV_IS_TONGA_P(asic_id.hw_internal_rev) ||
				ASIC_REV_IS_FIJI_P(asic_id.hw_internal_rev)) {
			dc_version = DCE_VERSION_10_0;
			break;
		}
		if (ASIC_REV_IS_POLARIS10_P(asic_id.hw_internal_rev) ||
				ASIC_REV_IS_POLARIS11_M(asic_id.hw_internal_rev) ||
				ASIC_REV_IS_POLARIS12_V(asic_id.hw_internal_rev)) {
			dc_version = DCE_VERSION_11_2;
		}
		if (ASIC_REV_IS_VEGAM(asic_id.hw_internal_rev))
			dc_version = DCE_VERSION_11_22;
		break;
	case FAMILY_AI:
		dc_version = DCE_VERSION_12_0;
		break;
#if defined(CONFIG_DRM_AMD_DC_DCN1_0)
	case FAMILY_RV:
		dc_version = DCN_VERSION_1_0;
		break;
#endif
	default:
		dc_version = DCE_VERSION_UNKNOWN;
		break;
	}
	return dc_version;
}