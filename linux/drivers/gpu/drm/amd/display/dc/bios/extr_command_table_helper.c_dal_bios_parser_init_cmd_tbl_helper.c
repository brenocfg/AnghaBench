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
#define  DCE_VERSION_10_0 134 
#define  DCE_VERSION_11_0 133 
#define  DCE_VERSION_11_2 132 
#define  DCE_VERSION_11_22 131 
#define  DCE_VERSION_8_0 130 
#define  DCE_VERSION_8_1 129 
#define  DCE_VERSION_8_3 128 
 struct command_table_helper* dal_cmd_tbl_helper_dce110_get_table () ; 
 struct command_table_helper* dal_cmd_tbl_helper_dce112_get_table () ; 
 struct command_table_helper* dal_cmd_tbl_helper_dce80_get_table () ; 

bool dal_bios_parser_init_cmd_tbl_helper(
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
		*h = dal_cmd_tbl_helper_dce112_get_table();
		return true;

	default:
		/* Unsupported DCE */
		BREAK_TO_DEBUGGER();
		return false;
	}
}