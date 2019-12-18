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
struct command_table_helper {int dummy; } ;
typedef  enum dce_version { ____Placeholder_dce_version } dce_version ;

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
 struct command_table_helper* dal_cmd_tbl_helper_dce110_get_table () ; 
 struct command_table_helper* dal_cmd_tbl_helper_dce112_get_table2 () ; 
 struct command_table_helper* dal_cmd_tbl_helper_dce80_get_table () ; 

bool dal_bios_parser_init_cmd_tbl_helper2(
	const struct command_table_helper **h,
	enum dce_version dce)
{
	switch (dce) {
	case DCE_VERSION_8_0:
	case DCE_VERSION_8_1:
	case DCE_VERSION_8_3:
		*h = dal_cmd_tbl_helper_dce80_get_table();
		return true;

	case DCE_VERSION_10_0:
		*h = dal_cmd_tbl_helper_dce110_get_table();
		return true;

	case DCE_VERSION_11_0:
		*h = dal_cmd_tbl_helper_dce110_get_table();
		return true;

	case DCE_VERSION_11_2:
	case DCE_VERSION_11_22:
		*h = dal_cmd_tbl_helper_dce112_get_table2();
		return true;
#if defined(CONFIG_DRM_AMD_DC_DCN1_0)
	case DCN_VERSION_1_0:
	case DCN_VERSION_1_01:
		*h = dal_cmd_tbl_helper_dce112_get_table2();
		return true;
#endif

#if defined(CONFIG_DRM_AMD_DC_DCN2_0)
	case DCN_VERSION_2_0:
		*h = dal_cmd_tbl_helper_dce112_get_table2();
		return true;
#endif
#if defined(CONFIG_DRM_AMD_DC_DCN2_1)
	case DCN_VERSION_2_1:
		*h = dal_cmd_tbl_helper_dce112_get_table2();
		return true;
#endif
	case DCE_VERSION_12_0:
	case DCE_VERSION_12_1:
		*h = dal_cmd_tbl_helper_dce112_get_table2();
		return true;

	default:
		/* Unsupported DCE */
		BREAK_TO_DEBUGGER();
		return false;
	}
}