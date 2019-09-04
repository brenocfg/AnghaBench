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
typedef  enum graphics_csc_adjust_type { ____Placeholder_graphics_csc_adjust_type } graphics_csc_adjust_type ;
typedef  enum dc_color_space { ____Placeholder_dc_color_space } dc_color_space ;
typedef  enum csc_color_mode { ____Placeholder_csc_color_mode } csc_color_mode ;

/* Variables and functions */
#define  COLOR_SPACE_SRGB 133 
#define  COLOR_SPACE_SRGB_LIMITED 132 
#define  COLOR_SPACE_YCBCR601 131 
#define  COLOR_SPACE_YCBCR601_LIMITED 130 
#define  COLOR_SPACE_YCBCR709 129 
#define  COLOR_SPACE_YCBCR709_LIMITED 128 
 int CSC_COLOR_MODE_GRAPHICS_OUTPUT_CSC ; 
 int GRAPHICS_CSC_ADJUST_TYPE_HW ; 
 int GRAPHICS_CSC_ADJUST_TYPE_SW ; 
 int /*<<< orphan*/  OUTPUT_CSC_CONTROL ; 
 int /*<<< orphan*/  OUTPUT_CSC_GRPH_MODE ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool configure_graphics_mode(
	struct dce_transform *xfm_dce,
	enum csc_color_mode config,
	enum graphics_csc_adjust_type csc_adjust_type,
	enum dc_color_space color_space)
{
	REG_SET(OUTPUT_CSC_CONTROL, 0,
		OUTPUT_CSC_GRPH_MODE, 0);

	if (csc_adjust_type == GRAPHICS_CSC_ADJUST_TYPE_SW) {
		if (config == CSC_COLOR_MODE_GRAPHICS_OUTPUT_CSC) {
			REG_SET(OUTPUT_CSC_CONTROL, 0,
				OUTPUT_CSC_GRPH_MODE, 4);
		} else {

			switch (color_space) {
			case COLOR_SPACE_SRGB:
				/* by pass */
				REG_SET(OUTPUT_CSC_CONTROL, 0,
					OUTPUT_CSC_GRPH_MODE, 0);
				break;
			case COLOR_SPACE_SRGB_LIMITED:
				/* TV RGB */
				REG_SET(OUTPUT_CSC_CONTROL, 0,
					OUTPUT_CSC_GRPH_MODE, 1);
				break;
			case COLOR_SPACE_YCBCR601:
			case COLOR_SPACE_YCBCR601_LIMITED:
				/* YCbCr601 */
				REG_SET(OUTPUT_CSC_CONTROL, 0,
					OUTPUT_CSC_GRPH_MODE, 2);
				break;
			case COLOR_SPACE_YCBCR709:
			case COLOR_SPACE_YCBCR709_LIMITED:
				/* YCbCr709 */
				REG_SET(OUTPUT_CSC_CONTROL, 0,
					OUTPUT_CSC_GRPH_MODE, 3);
				break;
			default:
				return false;
			}
		}
	} else if (csc_adjust_type == GRAPHICS_CSC_ADJUST_TYPE_HW) {
		switch (color_space) {
		case COLOR_SPACE_SRGB:
			/* by pass */
			REG_SET(OUTPUT_CSC_CONTROL, 0,
				OUTPUT_CSC_GRPH_MODE, 0);
			break;
			break;
		case COLOR_SPACE_SRGB_LIMITED:
			/* TV RGB */
			REG_SET(OUTPUT_CSC_CONTROL, 0,
				OUTPUT_CSC_GRPH_MODE, 1);
			break;
		case COLOR_SPACE_YCBCR601:
		case COLOR_SPACE_YCBCR601_LIMITED:
			/* YCbCr601 */
			REG_SET(OUTPUT_CSC_CONTROL, 0,
				OUTPUT_CSC_GRPH_MODE, 2);
			break;
		case COLOR_SPACE_YCBCR709:
		case COLOR_SPACE_YCBCR709_LIMITED:
			 /* YCbCr709 */
			REG_SET(OUTPUT_CSC_CONTROL, 0,
				OUTPUT_CSC_GRPH_MODE, 3);
			break;
		default:
			return false;
		}

	} else
		/* by pass */
		REG_SET(OUTPUT_CSC_CONTROL, 0,
			OUTPUT_CSC_GRPH_MODE, 0);

	return true;
}