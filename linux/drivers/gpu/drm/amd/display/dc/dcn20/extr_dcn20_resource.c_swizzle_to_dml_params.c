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

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
#define  DC_SW_4KB_D 143 
#define  DC_SW_4KB_D_X 142 
#define  DC_SW_4KB_S 141 
#define  DC_SW_4KB_S_X 140 
#define  DC_SW_64KB_D 139 
#define  DC_SW_64KB_D_T 138 
#define  DC_SW_64KB_D_X 137 
#define  DC_SW_64KB_R_X 136 
#define  DC_SW_64KB_S 135 
#define  DC_SW_64KB_S_T 134 
#define  DC_SW_64KB_S_X 133 
#define  DC_SW_LINEAR 132 
#define  DC_SW_VAR_D 131 
#define  DC_SW_VAR_D_X 130 
#define  DC_SW_VAR_S 129 
#define  DC_SW_VAR_S_X 128 
 unsigned int dm_sw_4kb_d ; 
 unsigned int dm_sw_4kb_d_x ; 
 unsigned int dm_sw_4kb_s ; 
 unsigned int dm_sw_4kb_s_x ; 
 unsigned int dm_sw_64kb_d ; 
 unsigned int dm_sw_64kb_d_t ; 
 unsigned int dm_sw_64kb_d_x ; 
 unsigned int dm_sw_64kb_r_x ; 
 unsigned int dm_sw_64kb_s ; 
 unsigned int dm_sw_64kb_s_t ; 
 unsigned int dm_sw_64kb_s_x ; 
 unsigned int dm_sw_linear ; 
 unsigned int dm_sw_var_d ; 
 unsigned int dm_sw_var_d_x ; 
 unsigned int dm_sw_var_s ; 
 unsigned int dm_sw_var_s_x ; 

__attribute__((used)) static void swizzle_to_dml_params(
		enum swizzle_mode_values swizzle,
		unsigned int *sw_mode)
{
	switch (swizzle) {
	case DC_SW_LINEAR:
		*sw_mode = dm_sw_linear;
		break;
	case DC_SW_4KB_S:
		*sw_mode = dm_sw_4kb_s;
		break;
	case DC_SW_4KB_S_X:
		*sw_mode = dm_sw_4kb_s_x;
		break;
	case DC_SW_4KB_D:
		*sw_mode = dm_sw_4kb_d;
		break;
	case DC_SW_4KB_D_X:
		*sw_mode = dm_sw_4kb_d_x;
		break;
	case DC_SW_64KB_S:
		*sw_mode = dm_sw_64kb_s;
		break;
	case DC_SW_64KB_S_X:
		*sw_mode = dm_sw_64kb_s_x;
		break;
	case DC_SW_64KB_S_T:
		*sw_mode = dm_sw_64kb_s_t;
		break;
	case DC_SW_64KB_D:
		*sw_mode = dm_sw_64kb_d;
		break;
	case DC_SW_64KB_D_X:
		*sw_mode = dm_sw_64kb_d_x;
		break;
	case DC_SW_64KB_D_T:
		*sw_mode = dm_sw_64kb_d_t;
		break;
	case DC_SW_64KB_R_X:
		*sw_mode = dm_sw_64kb_r_x;
		break;
	case DC_SW_VAR_S:
		*sw_mode = dm_sw_var_s;
		break;
	case DC_SW_VAR_S_X:
		*sw_mode = dm_sw_var_s_x;
		break;
	case DC_SW_VAR_D:
		*sw_mode = dm_sw_var_d;
		break;
	case DC_SW_VAR_D_X:
		*sw_mode = dm_sw_var_d_x;
		break;

	default:
		ASSERT(0); /* Not supported */
		break;
	}
}