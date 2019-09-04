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
#define  DCE_VERSION_10_0 135 
#define  DCE_VERSION_11_0 134 
#define  DCE_VERSION_11_2 133 
#define  DCE_VERSION_11_22 132 
#define  DCE_VERSION_12_0 131 
#define  DCE_VERSION_8_0 130 
#define  DCE_VERSION_8_1 129 
#define  DCE_VERSION_8_3 128 
 scalar_t__ IS_FPGA_MAXIMUS_DC (int) ; 
 int /*<<< orphan*/  dal_hw_translate_dce110_init (struct hw_translate*) ; 
 int /*<<< orphan*/  dal_hw_translate_dce120_init (struct hw_translate*) ; 
 int /*<<< orphan*/  dal_hw_translate_dce80_init (struct hw_translate*) ; 
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
		dal_hw_translate_dce120_init(translate);
		return true;
#if defined(CONFIG_DRM_AMD_DC_DCN1_0)
	case DCN_VERSION_1_0:
		dal_hw_translate_dcn10_init(translate);
		return true;
#endif

	default:
		BREAK_TO_DEBUGGER();
		return false;
	}
}