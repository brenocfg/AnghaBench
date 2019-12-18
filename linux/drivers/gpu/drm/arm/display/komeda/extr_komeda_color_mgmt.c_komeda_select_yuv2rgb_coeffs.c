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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
#define  DRM_COLOR_YCBCR_BT2020 130 
#define  DRM_COLOR_YCBCR_BT601 129 
#define  DRM_COLOR_YCBCR_BT709 128 
 scalar_t__ DRM_COLOR_YCBCR_LIMITED_RANGE ; 
 int /*<<< orphan*/ * yuv2rgb_bt2020 ; 
 int /*<<< orphan*/ * yuv2rgb_bt601_narrow ; 
 int /*<<< orphan*/ * yuv2rgb_bt601_wide ; 
 int /*<<< orphan*/ * yuv2rgb_bt709_narrow ; 
 int /*<<< orphan*/ * yuv2rgb_bt709_wide ; 

const s32 *komeda_select_yuv2rgb_coeffs(u32 color_encoding, u32 color_range)
{
	bool narrow = color_range == DRM_COLOR_YCBCR_LIMITED_RANGE;
	const s32 *coeffs;

	switch (color_encoding) {
	case DRM_COLOR_YCBCR_BT709:
		coeffs = narrow ? yuv2rgb_bt709_narrow : yuv2rgb_bt709_wide;
		break;
	case DRM_COLOR_YCBCR_BT601:
		coeffs = narrow ? yuv2rgb_bt601_narrow : yuv2rgb_bt601_wide;
		break;
	case DRM_COLOR_YCBCR_BT2020:
		coeffs = yuv2rgb_bt2020;
		break;
	default:
		coeffs = NULL;
		break;
	}

	return coeffs;
}