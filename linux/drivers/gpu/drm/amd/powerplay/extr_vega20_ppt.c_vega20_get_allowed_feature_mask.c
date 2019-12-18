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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct smu_context {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FEATURE_ACDC_BIT ; 
 int /*<<< orphan*/  FEATURE_CG_BIT ; 
 int /*<<< orphan*/  FEATURE_DPM_DCEFCLK_BIT ; 
 int /*<<< orphan*/  FEATURE_DPM_FCLK_BIT ; 
 int /*<<< orphan*/  FEATURE_DPM_GFXCLK_BIT ; 
 int /*<<< orphan*/  FEATURE_DPM_LINK_BIT ; 
 int /*<<< orphan*/  FEATURE_DPM_MP0CLK_BIT ; 
 int /*<<< orphan*/  FEATURE_DPM_PREFETCHER_BIT ; 
 int /*<<< orphan*/  FEATURE_DPM_SOCCLK_BIT ; 
 int /*<<< orphan*/  FEATURE_DPM_UCLK_BIT ; 
 int /*<<< orphan*/  FEATURE_DPM_UVD_BIT ; 
 int /*<<< orphan*/  FEATURE_DPM_VCE_BIT ; 
 int /*<<< orphan*/  FEATURE_FAN_CONTROL_BIT ; 
 int /*<<< orphan*/  FEATURE_FW_CTF_BIT ; 
 int /*<<< orphan*/  FEATURE_GFXOFF_BIT ; 
 int /*<<< orphan*/  FEATURE_GFX_EDC_BIT ; 
 int /*<<< orphan*/  FEATURE_GFX_PER_CU_CG_BIT ; 
 int /*<<< orphan*/  FEATURE_LED_DISPLAY_BIT ; 
 int FEATURE_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FEATURE_PPT_BIT ; 
 int /*<<< orphan*/  FEATURE_RM_BIT ; 
 int /*<<< orphan*/  FEATURE_TDC_BIT ; 
 int /*<<< orphan*/  FEATURE_THERMAL_BIT ; 
 int /*<<< orphan*/  FEATURE_ULV_BIT ; 
 int /*<<< orphan*/  FEATURE_VR0HOT_BIT ; 
 int /*<<< orphan*/  FEATURE_VR1HOT_BIT ; 
 int /*<<< orphan*/  FEATURE_XGMI_BIT ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
vega20_get_allowed_feature_mask(struct smu_context *smu,
				  uint32_t *feature_mask, uint32_t num)
{
	if (num > 2)
		return -EINVAL;

	memset(feature_mask, 0, sizeof(uint32_t) * num);

	*(uint64_t *)feature_mask |= FEATURE_MASK(FEATURE_DPM_PREFETCHER_BIT)
				| FEATURE_MASK(FEATURE_DPM_GFXCLK_BIT)
				| FEATURE_MASK(FEATURE_DPM_UCLK_BIT)
				| FEATURE_MASK(FEATURE_DPM_SOCCLK_BIT)
				| FEATURE_MASK(FEATURE_DPM_UVD_BIT)
				| FEATURE_MASK(FEATURE_DPM_VCE_BIT)
				| FEATURE_MASK(FEATURE_ULV_BIT)
				| FEATURE_MASK(FEATURE_DPM_MP0CLK_BIT)
				| FEATURE_MASK(FEATURE_DPM_LINK_BIT)
				| FEATURE_MASK(FEATURE_DPM_DCEFCLK_BIT)
				| FEATURE_MASK(FEATURE_PPT_BIT)
				| FEATURE_MASK(FEATURE_TDC_BIT)
				| FEATURE_MASK(FEATURE_THERMAL_BIT)
				| FEATURE_MASK(FEATURE_GFX_PER_CU_CG_BIT)
				| FEATURE_MASK(FEATURE_RM_BIT)
				| FEATURE_MASK(FEATURE_ACDC_BIT)
				| FEATURE_MASK(FEATURE_VR0HOT_BIT)
				| FEATURE_MASK(FEATURE_VR1HOT_BIT)
				| FEATURE_MASK(FEATURE_FW_CTF_BIT)
				| FEATURE_MASK(FEATURE_LED_DISPLAY_BIT)
				| FEATURE_MASK(FEATURE_FAN_CONTROL_BIT)
				| FEATURE_MASK(FEATURE_GFX_EDC_BIT)
				| FEATURE_MASK(FEATURE_GFXOFF_BIT)
				| FEATURE_MASK(FEATURE_CG_BIT)
				| FEATURE_MASK(FEATURE_DPM_FCLK_BIT)
				| FEATURE_MASK(FEATURE_XGMI_BIT);
	return 0;
}