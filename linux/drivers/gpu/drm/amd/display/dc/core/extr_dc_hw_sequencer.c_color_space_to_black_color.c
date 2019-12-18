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
struct tg_color {int dummy; } ;
struct dc {int dummy; } ;
typedef  enum dc_color_space { ____Placeholder_dc_color_space } dc_color_space ;

/* Variables and functions */
 size_t BLACK_COLOR_FORMAT_RGB_FULLRANGE ; 
 size_t BLACK_COLOR_FORMAT_RGB_LIMITED ; 
 size_t BLACK_COLOR_FORMAT_YUV_CV ; 
#define  COLOR_SPACE_2020_RGB_FULLRANGE 148 
#define  COLOR_SPACE_2020_RGB_LIMITEDRANGE 147 
#define  COLOR_SPACE_2020_YCBCR 146 
#define  COLOR_SPACE_ADOBERGB 145 
#define  COLOR_SPACE_APPCTRL 144 
#define  COLOR_SPACE_CUSTOMPOINTS 143 
#define  COLOR_SPACE_DCIP3 142 
#define  COLOR_SPACE_DISPLAYNATIVE 141 
#define  COLOR_SPACE_DOLBYVISION 140 
#define  COLOR_SPACE_MSREF_SCRGB 139 
#define  COLOR_SPACE_SRGB 138 
#define  COLOR_SPACE_SRGB_LIMITED 137 
#define  COLOR_SPACE_UNKNOWN 136 
#define  COLOR_SPACE_XR_RGB 135 
#define  COLOR_SPACE_XV_YCC_601 134 
#define  COLOR_SPACE_XV_YCC_709 133 
#define  COLOR_SPACE_YCBCR601 132 
#define  COLOR_SPACE_YCBCR601_LIMITED 131 
#define  COLOR_SPACE_YCBCR709 130 
#define  COLOR_SPACE_YCBCR709_BLACK 129 
#define  COLOR_SPACE_YCBCR709_LIMITED 128 
 struct tg_color* black_color_format ; 

void color_space_to_black_color(
	const struct dc *dc,
	enum dc_color_space colorspace,
	struct tg_color *black_color)
{
	switch (colorspace) {
	case COLOR_SPACE_YCBCR601:
	case COLOR_SPACE_YCBCR709:
	case COLOR_SPACE_YCBCR709_BLACK:
	case COLOR_SPACE_YCBCR601_LIMITED:
	case COLOR_SPACE_YCBCR709_LIMITED:
	case COLOR_SPACE_2020_YCBCR:
		*black_color = black_color_format[BLACK_COLOR_FORMAT_YUV_CV];
		break;

	case COLOR_SPACE_SRGB_LIMITED:
		*black_color =
			black_color_format[BLACK_COLOR_FORMAT_RGB_LIMITED];
		break;

	/**
	 * Remove default and add case for all color space
	 * so when we forget to add new color space
	 * compiler will give a warning
	 */
	case COLOR_SPACE_UNKNOWN:
	case COLOR_SPACE_SRGB:
	case COLOR_SPACE_XR_RGB:
	case COLOR_SPACE_MSREF_SCRGB:
	case COLOR_SPACE_XV_YCC_709:
	case COLOR_SPACE_XV_YCC_601:
	case COLOR_SPACE_2020_RGB_FULLRANGE:
	case COLOR_SPACE_2020_RGB_LIMITEDRANGE:
	case COLOR_SPACE_ADOBERGB:
	case COLOR_SPACE_DCIP3:
	case COLOR_SPACE_DISPLAYNATIVE:
	case COLOR_SPACE_DOLBYVISION:
	case COLOR_SPACE_APPCTRL:
	case COLOR_SPACE_CUSTOMPOINTS:
		/* fefault is sRGB black (full range). */
		*black_color =
			black_color_format[BLACK_COLOR_FORMAT_RGB_FULLRANGE];
		/* default is sRGB black 0. */
		break;
	}
}