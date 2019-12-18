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
typedef  enum omap_color_mode { ____Placeholder_omap_color_mode } omap_color_mode ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  OMAP_DSS_COLOR_ARGB16 146 
#define  OMAP_DSS_COLOR_ARGB16_1555 145 
#define  OMAP_DSS_COLOR_ARGB32 144 
#define  OMAP_DSS_COLOR_CLUT1 143 
#define  OMAP_DSS_COLOR_CLUT2 142 
#define  OMAP_DSS_COLOR_CLUT4 141 
#define  OMAP_DSS_COLOR_CLUT8 140 
#define  OMAP_DSS_COLOR_NV12 139 
#define  OMAP_DSS_COLOR_RGB12U 138 
#define  OMAP_DSS_COLOR_RGB16 137 
#define  OMAP_DSS_COLOR_RGB24P 136 
#define  OMAP_DSS_COLOR_RGB24U 135 
#define  OMAP_DSS_COLOR_RGBA16 134 
#define  OMAP_DSS_COLOR_RGBA32 133 
#define  OMAP_DSS_COLOR_RGBX16 132 
#define  OMAP_DSS_COLOR_RGBX32 131 
#define  OMAP_DSS_COLOR_UYVY 130 
#define  OMAP_DSS_COLOR_XRGB16_1555 129 
#define  OMAP_DSS_COLOR_YUV2 128 

__attribute__((used)) static int color_mode_to_bpp(enum omap_color_mode color_mode)
{
	switch (color_mode) {
	case OMAP_DSS_COLOR_CLUT1:
		return 1;
	case OMAP_DSS_COLOR_CLUT2:
		return 2;
	case OMAP_DSS_COLOR_CLUT4:
		return 4;
	case OMAP_DSS_COLOR_CLUT8:
	case OMAP_DSS_COLOR_NV12:
		return 8;
	case OMAP_DSS_COLOR_RGB12U:
	case OMAP_DSS_COLOR_RGB16:
	case OMAP_DSS_COLOR_ARGB16:
	case OMAP_DSS_COLOR_YUV2:
	case OMAP_DSS_COLOR_UYVY:
	case OMAP_DSS_COLOR_RGBA16:
	case OMAP_DSS_COLOR_RGBX16:
	case OMAP_DSS_COLOR_ARGB16_1555:
	case OMAP_DSS_COLOR_XRGB16_1555:
		return 16;
	case OMAP_DSS_COLOR_RGB24P:
		return 24;
	case OMAP_DSS_COLOR_RGB24U:
	case OMAP_DSS_COLOR_ARGB32:
	case OMAP_DSS_COLOR_RGBA32:
	case OMAP_DSS_COLOR_RGBX32:
		return 32;
	default:
		BUG();
		return 0;
	}
}