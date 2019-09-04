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
typedef  enum swizzle_mode_values { ____Placeholder_swizzle_mode_values } swizzle_mode_values ;
typedef  enum dcn_bw_defs { ____Placeholder_dcn_bw_defs } dcn_bw_defs ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
#define  DC_SW_256B_S 151 
#define  DC_SW_256_D 150 
#define  DC_SW_256_R 149 
#define  DC_SW_4KB_D 148 
#define  DC_SW_4KB_D_X 147 
#define  DC_SW_4KB_R 146 
#define  DC_SW_4KB_R_X 145 
#define  DC_SW_4KB_S 144 
#define  DC_SW_4KB_S_X 143 
#define  DC_SW_64KB_D 142 
#define  DC_SW_64KB_D_T 141 
#define  DC_SW_64KB_D_X 140 
#define  DC_SW_64KB_R 139 
#define  DC_SW_64KB_R_X 138 
#define  DC_SW_64KB_S 137 
#define  DC_SW_64KB_S_T 136 
#define  DC_SW_64KB_S_X 135 
#define  DC_SW_LINEAR 134 
#define  DC_SW_VAR_D 133 
#define  DC_SW_VAR_D_X 132 
#define  DC_SW_VAR_R 131 
#define  DC_SW_VAR_R_X 130 
#define  DC_SW_VAR_S 129 
#define  DC_SW_VAR_S_X 128 
 int dcn_bw_sw_4_kb_d ; 
 int dcn_bw_sw_4_kb_d_x ; 
 int dcn_bw_sw_4_kb_s ; 
 int dcn_bw_sw_4_kb_s_x ; 
 int dcn_bw_sw_64_kb_d ; 
 int dcn_bw_sw_64_kb_d_t ; 
 int dcn_bw_sw_64_kb_d_x ; 
 int dcn_bw_sw_64_kb_s ; 
 int dcn_bw_sw_64_kb_s_t ; 
 int dcn_bw_sw_64_kb_s_x ; 
 int dcn_bw_sw_linear ; 
 int dcn_bw_sw_var_d ; 
 int dcn_bw_sw_var_d_x ; 
 int dcn_bw_sw_var_s ; 
 int dcn_bw_sw_var_s_x ; 

__attribute__((used)) static enum dcn_bw_defs tl_sw_mode_to_bw_defs(enum swizzle_mode_values sw_mode)
{
	switch (sw_mode) {
	case DC_SW_LINEAR:
		return dcn_bw_sw_linear;
	case DC_SW_4KB_S:
		return dcn_bw_sw_4_kb_s;
	case DC_SW_4KB_D:
		return dcn_bw_sw_4_kb_d;
	case DC_SW_64KB_S:
		return dcn_bw_sw_64_kb_s;
	case DC_SW_64KB_D:
		return dcn_bw_sw_64_kb_d;
	case DC_SW_VAR_S:
		return dcn_bw_sw_var_s;
	case DC_SW_VAR_D:
		return dcn_bw_sw_var_d;
	case DC_SW_64KB_S_T:
		return dcn_bw_sw_64_kb_s_t;
	case DC_SW_64KB_D_T:
		return dcn_bw_sw_64_kb_d_t;
	case DC_SW_4KB_S_X:
		return dcn_bw_sw_4_kb_s_x;
	case DC_SW_4KB_D_X:
		return dcn_bw_sw_4_kb_d_x;
	case DC_SW_64KB_S_X:
		return dcn_bw_sw_64_kb_s_x;
	case DC_SW_64KB_D_X:
		return dcn_bw_sw_64_kb_d_x;
	case DC_SW_VAR_S_X:
		return dcn_bw_sw_var_s_x;
	case DC_SW_VAR_D_X:
		return dcn_bw_sw_var_d_x;
	case DC_SW_256B_S:
	case DC_SW_256_D:
	case DC_SW_256_R:
	case DC_SW_4KB_R:
	case DC_SW_64KB_R:
	case DC_SW_VAR_R:
	case DC_SW_4KB_R_X:
	case DC_SW_64KB_R_X:
	case DC_SW_VAR_R_X:
	default:
		BREAK_TO_DEBUGGER(); /*not in formula*/
		return dcn_bw_sw_4_kb_s;
	}
}