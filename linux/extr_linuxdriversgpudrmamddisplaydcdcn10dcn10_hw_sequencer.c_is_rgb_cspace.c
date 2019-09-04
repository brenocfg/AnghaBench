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
typedef  enum dc_color_space { ____Placeholder_dc_color_space } dc_color_space ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
#define  COLOR_SPACE_2020_RGB_FULLRANGE 137 
#define  COLOR_SPACE_2020_RGB_LIMITEDRANGE 136 
#define  COLOR_SPACE_2020_YCBCR 135 
#define  COLOR_SPACE_ADOBERGB 134 
#define  COLOR_SPACE_SRGB 133 
#define  COLOR_SPACE_SRGB_LIMITED 132 
#define  COLOR_SPACE_YCBCR601 131 
#define  COLOR_SPACE_YCBCR601_LIMITED 130 
#define  COLOR_SPACE_YCBCR709 129 
#define  COLOR_SPACE_YCBCR709_LIMITED 128 

bool is_rgb_cspace(enum dc_color_space output_color_space)
{
	switch (output_color_space) {
	case COLOR_SPACE_SRGB:
	case COLOR_SPACE_SRGB_LIMITED:
	case COLOR_SPACE_2020_RGB_FULLRANGE:
	case COLOR_SPACE_2020_RGB_LIMITEDRANGE:
	case COLOR_SPACE_ADOBERGB:
		return true;
	case COLOR_SPACE_YCBCR601:
	case COLOR_SPACE_YCBCR709:
	case COLOR_SPACE_YCBCR601_LIMITED:
	case COLOR_SPACE_YCBCR709_LIMITED:
	case COLOR_SPACE_2020_YCBCR:
		return false;
	default:
		/* Add a case to switch */
		BREAK_TO_DEBUGGER();
		return false;
	}
}