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
typedef  int u32 ;

/* Variables and functions */
#define  DRM_FORMAT_ARGB1555 147 
#define  DRM_FORMAT_ARGB2101010 146 
#define  DRM_FORMAT_ARGB8888 145 
#define  DRM_FORMAT_BGRA1010102 144 
#define  DRM_FORMAT_BGRA5551 143 
#define  DRM_FORMAT_BGRA8888 142 
#define  DRM_FORMAT_BGRX8888 141 
#define  DRM_FORMAT_RGB565 140 
#define  DRM_FORMAT_RGB888 139 
#define  DRM_FORMAT_RGBA1010102 138 
#define  DRM_FORMAT_RGBA5551 137 
#define  DRM_FORMAT_RGBA8888 136 
#define  DRM_FORMAT_RGBX8888 135 
#define  DRM_FORMAT_UYVY 134 
#define  DRM_FORMAT_X0L0 133 
#define  DRM_FORMAT_X0L2 132 
#define  DRM_FORMAT_XBGR8888 131 
#define  DRM_FORMAT_XRGB8888 130 
#define  DRM_FORMAT_XVYU2101010 129 
#define  DRM_FORMAT_XYUV8888 128 

bool malidp_hw_format_is_linear_only(u32 format)
{
	switch (format) {
	case DRM_FORMAT_ARGB2101010:
	case DRM_FORMAT_RGBA1010102:
	case DRM_FORMAT_BGRA1010102:
	case DRM_FORMAT_ARGB8888:
	case DRM_FORMAT_RGBA8888:
	case DRM_FORMAT_BGRA8888:
	case DRM_FORMAT_XBGR8888:
	case DRM_FORMAT_XRGB8888:
	case DRM_FORMAT_RGBX8888:
	case DRM_FORMAT_BGRX8888:
	case DRM_FORMAT_RGB888:
	case DRM_FORMAT_RGB565:
	case DRM_FORMAT_ARGB1555:
	case DRM_FORMAT_RGBA5551:
	case DRM_FORMAT_BGRA5551:
	case DRM_FORMAT_UYVY:
	case DRM_FORMAT_XYUV8888:
	case DRM_FORMAT_XVYU2101010:
	case DRM_FORMAT_X0L2:
	case DRM_FORMAT_X0L0:
		return true;
	default:
		return false;
	}
}