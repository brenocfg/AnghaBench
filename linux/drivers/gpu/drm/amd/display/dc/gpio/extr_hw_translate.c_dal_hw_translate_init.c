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
struct hw_translate {int dummy; } ;
typedef  enum dce_version { ____Placeholder_dce_version } dce_version ;
typedef  enum dce_environment { ____Placeholder_dce_environment } dce_environment ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
#define  DCE_VERSION_10_0 140 
#define  DCE_VERSION_11_0 139 
#define  DCE_VERSION_11_2 138 
#define  DCE_VERSION_11_22 137 
#define  DCE_VERSION_12_0 136 
#define  DCE_VERSION_12_1 135 
#define  DCE_VERSION_8_0 134 
#define  DCE_VERSION_8_1 133 
#define  DCE_VERSION_8_3 132 
#define  DCN_VERSION_1_0 131 
#define  DCN_VERSION_1_01 130 
#define  DCN_VERSION_2_0 129 
#define  DCN_VERSION_2_1 128 
 scalar_t__ IS_FPGA_MAXIMUS_DC (int) ; 
 int /*<<< orphan*/  dal_hw_translate_dce110_init (struct hw_translate*) ; 
 int /*<<< orphan*/  dal_hw_translate_dce120_init (struct hw_translate*) ; 
 int /*<<< orphan*/  dal_hw_translate_dce80_init (struct hw_translate*) ; 
 int /*<<< orphan*/  dal_hw_translate_dcn10_init (struct hw_translate*) ; 
 int /*<<< orphan*/  dal_hw_translate_dcn20_init (struct hw_translate*) ; 
 int /*<<< orphan*/  dal_hw_translate_dcn21_init (struct hw_translate*) ; 
 int /*<<< orphan*/  dal_hw_translate_diag_fpga_init (struct hw_translate*) ; 

bool dal_hw_translate_init(
	struct hw_translate *translate,
	enum dce_version dce_version,
	enum dce_environment dce_environment)
{
	if (IS_FPGA_MAXIMUS_DC(dce_environment)) {
		dal_hw_translate_diag_fpga_init(translate);
		return true;
	}

	switch (dce_version) {
	case DCE_VERSION_8_0:
	case DCE_VERSION_8_1:
	case DCE_VERSION_8_3:
		dal_hw_translate_dce80_init(translate);
		return true;
	case DCE_VERSION_10_0:
	case DCE_VERSION_11_0:
	case DCE_VERSION_11_2:
	case DCE_VERSION_11_22:
		dal_hw_translate_dce110_init(translate);
		return true;
	case DCE_VERSION_12_0:
	case DCE_VERSION_12_1:
		dal_hw_translate_dce120_init(translate);
		return true;
#if defined(CONFIG_DRM_AMD_DC_DCN1_0)
	case DCN_VERSION_1_0:
	case DCN_VERSION_1_01:
		dal_hw_translate_dcn10_init(translate);
		return true;
#endif

#if defined(CONFIG_DRM_AMD_DC_DCN2_0)
	case DCN_VERSION_2_0:
		dal_hw_translate_dcn20_init(translate);
		return true;
#endif
#if defined(CONFIG_DRM_AMD_DC_DCN2_1)
	case DCN_VERSION_2_1:
		dal_hw_translate_dcn21_init(translate);
		return true;
#endif

	default:
		BREAK_TO_DEBUGGER();
		return false;
	}
}