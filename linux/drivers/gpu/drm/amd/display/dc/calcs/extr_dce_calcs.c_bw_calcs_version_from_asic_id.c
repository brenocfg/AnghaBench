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
typedef  enum bw_calcs_version { ____Placeholder_bw_calcs_version } bw_calcs_version ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_REV_IS_POLARIS10_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASIC_REV_IS_POLARIS11_M (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASIC_REV_IS_POLARIS12_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASIC_REV_IS_STONEY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASIC_REV_IS_VEGAM (int /*<<< orphan*/ ) ; 
 int BW_CALCS_VERSION_CARRIZO ; 
 int BW_CALCS_VERSION_INVALID ; 
 int BW_CALCS_VERSION_POLARIS10 ; 
 int BW_CALCS_VERSION_POLARIS11 ; 
 int BW_CALCS_VERSION_POLARIS12 ; 
 int BW_CALCS_VERSION_STONEY ; 
 int BW_CALCS_VERSION_VEGA10 ; 
 int BW_CALCS_VERSION_VEGAM ; 
#define  FAMILY_AI 130 
#define  FAMILY_CZ 129 
#define  FAMILY_VI 128 

__attribute__((used)) static enum bw_calcs_version bw_calcs_version_from_asic_id(struct hw_asic_id asic_id)
{
	switch (asic_id.chip_family) {

	case FAMILY_CZ:
		if (ASIC_REV_IS_STONEY(asic_id.hw_internal_rev))
			return BW_CALCS_VERSION_STONEY;
		return BW_CALCS_VERSION_CARRIZO;

	case FAMILY_VI:
		if (ASIC_REV_IS_POLARIS12_V(asic_id.hw_internal_rev))
			return BW_CALCS_VERSION_POLARIS12;
		if (ASIC_REV_IS_POLARIS10_P(asic_id.hw_internal_rev))
			return BW_CALCS_VERSION_POLARIS10;
		if (ASIC_REV_IS_POLARIS11_M(asic_id.hw_internal_rev))
			return BW_CALCS_VERSION_POLARIS11;
		if (ASIC_REV_IS_VEGAM(asic_id.hw_internal_rev))
			return BW_CALCS_VERSION_VEGAM;
		return BW_CALCS_VERSION_INVALID;

	case FAMILY_AI:
		return BW_CALCS_VERSION_VEGA10;

	default:
		return BW_CALCS_VERSION_INVALID;
	}
}