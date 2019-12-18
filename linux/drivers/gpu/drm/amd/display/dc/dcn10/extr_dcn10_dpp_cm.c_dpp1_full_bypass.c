#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dpp {int dummy; } ;
struct dcn10_dpp {TYPE_1__* tf_mask; } ;
struct TYPE_2__ {scalar_t__ CM_BYPASS_EN; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_BYPASS ; 
 int /*<<< orphan*/  CM_BYPASS_EN ; 
 int /*<<< orphan*/  CM_CONTROL ; 
 int /*<<< orphan*/  CM_DGAM_CONTROL ; 
 int /*<<< orphan*/  CM_DGAM_LUT_MODE ; 
 int /*<<< orphan*/  CNVC_BYPASS ; 
 int /*<<< orphan*/  CNVC_SURFACE_PIXEL_FORMAT ; 
 int /*<<< orphan*/  FORMAT_CONTROL ; 
 int /*<<< orphan*/  FORMAT_CONTROL__ALPHA_EN ; 
 int /*<<< orphan*/  FORMAT_EXPANSION_MODE ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dcn10_dpp* TO_DCN10_DPP (struct dpp*) ; 

void dpp1_full_bypass(struct dpp *dpp_base)
{
	struct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	/* Input pixel format: ARGB8888 */
	REG_SET(CNVC_SURFACE_PIXEL_FORMAT, 0,
			CNVC_SURFACE_PIXEL_FORMAT, 0x8);

	/* Zero expansion */
	REG_SET_3(FORMAT_CONTROL, 0,
			CNVC_BYPASS, 0,
			FORMAT_CONTROL__ALPHA_EN, 0,
			FORMAT_EXPANSION_MODE, 0);

	/* COLOR_KEYER_CONTROL.COLOR_KEYER_EN = 0 this should be default */
	if (dpp->tf_mask->CM_BYPASS_EN)
		REG_SET(CM_CONTROL, 0, CM_BYPASS_EN, 1);
#if defined(CONFIG_DRM_AMD_DC_DCN2_0)
	else
		REG_SET(CM_CONTROL, 0, CM_BYPASS, 1);
#endif

	/* Setting degamma bypass for now */
	REG_SET(CM_DGAM_CONTROL, 0, CM_DGAM_LUT_MODE, 0);
}