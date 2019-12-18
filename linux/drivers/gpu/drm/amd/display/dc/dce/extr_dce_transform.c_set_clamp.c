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
struct dce_transform {int dummy; } ;
typedef  enum dc_color_depth { ____Placeholder_dc_color_depth } dc_color_depth ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
#define  COLOR_DEPTH_101010 131 
#define  COLOR_DEPTH_121212 130 
#define  COLOR_DEPTH_666 129 
#define  COLOR_DEPTH_888 128 
 int /*<<< orphan*/  OUT_CLAMP_CONTROL_B_CB ; 
 int /*<<< orphan*/  OUT_CLAMP_CONTROL_G_Y ; 
 int /*<<< orphan*/  OUT_CLAMP_CONTROL_R_CR ; 
 int /*<<< orphan*/  OUT_CLAMP_MAX_B_CB ; 
 int /*<<< orphan*/  OUT_CLAMP_MAX_G_Y ; 
 int /*<<< orphan*/  OUT_CLAMP_MAX_R_CR ; 
 int /*<<< orphan*/  OUT_CLAMP_MIN_B_CB ; 
 int /*<<< orphan*/  OUT_CLAMP_MIN_G_Y ; 
 int /*<<< orphan*/  OUT_CLAMP_MIN_R_CR ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_clamp(
	struct dce_transform *xfm_dce,
	enum dc_color_depth depth)
{
	int clamp_max = 0;

	/* At the clamp block the data will be MSB aligned, so we set the max
	 * clamp accordingly.
	 * For example, the max value for 6 bits MSB aligned (14 bit bus) would
	 * be "11 1111 0000 0000" in binary, so 0x3F00.
	 */
	switch (depth) {
	case COLOR_DEPTH_666:
		/* 6bit MSB aligned on 14 bit bus '11 1111 0000 0000' */
		clamp_max = 0x3F00;
		break;
	case COLOR_DEPTH_888:
		/* 8bit MSB aligned on 14 bit bus '11 1111 1100 0000' */
		clamp_max = 0x3FC0;
		break;
	case COLOR_DEPTH_101010:
		/* 10bit MSB aligned on 14 bit bus '11 1111 1111 1100' */
		clamp_max = 0x3FFC;
		break;
	case COLOR_DEPTH_121212:
		/* 12bit MSB aligned on 14 bit bus '11 1111 1111 1111' */
		clamp_max = 0x3FFF;
		break;
	default:
		clamp_max = 0x3FC0;
		BREAK_TO_DEBUGGER(); /* Invalid clamp bit depth */
	}
	REG_SET_2(OUT_CLAMP_CONTROL_B_CB, 0,
			OUT_CLAMP_MIN_B_CB, 0,
			OUT_CLAMP_MAX_B_CB, clamp_max);

	REG_SET_2(OUT_CLAMP_CONTROL_G_Y, 0,
			OUT_CLAMP_MIN_G_Y, 0,
			OUT_CLAMP_MAX_G_Y, clamp_max);

	REG_SET_2(OUT_CLAMP_CONTROL_R_CR, 0,
			OUT_CLAMP_MIN_R_CR, 0,
			OUT_CLAMP_MAX_R_CR, clamp_max);
}