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
struct dpp {int dummy; } ;
struct dcn20_dpp {int dummy; } ;
typedef  enum ipp_degamma_mode { ____Placeholder_ipp_degamma_mode } ipp_degamma_mode ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  CM_DGAM_CONTROL ; 
 int /*<<< orphan*/  CM_DGAM_LUT_MODE ; 
#define  IPP_DEGAMMA_MODE_BYPASS 130 
#define  IPP_DEGAMMA_MODE_HW_sRGB 129 
#define  IPP_DEGAMMA_MODE_HW_xvYCC 128 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dcn20_dpp* TO_DCN20_DPP (struct dpp*) ; 
 int /*<<< orphan*/  dpp2_enable_cm_block (struct dpp*) ; 

void dpp2_set_degamma(
		struct dpp *dpp_base,
		enum ipp_degamma_mode mode)
{
	struct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);
	dpp2_enable_cm_block(dpp_base);

	switch (mode) {
	case IPP_DEGAMMA_MODE_BYPASS:
		/* Setting de gamma bypass for now */
		REG_UPDATE(CM_DGAM_CONTROL, CM_DGAM_LUT_MODE, 0);
		break;
	case IPP_DEGAMMA_MODE_HW_sRGB:
		REG_UPDATE(CM_DGAM_CONTROL, CM_DGAM_LUT_MODE, 1);
		break;
	case IPP_DEGAMMA_MODE_HW_xvYCC:
		REG_UPDATE(CM_DGAM_CONTROL, CM_DGAM_LUT_MODE, 2);
			break;
	default:
		BREAK_TO_DEBUGGER();
		break;
	}
}