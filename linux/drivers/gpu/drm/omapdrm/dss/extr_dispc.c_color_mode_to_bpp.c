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
 int /*<<< orphan*/  BUG () ; 
#define  DRM_FORMAT_ARGB1555 142 
#define  DRM_FORMAT_ARGB4444 141 
#define  DRM_FORMAT_ARGB8888 140 
#define  DRM_FORMAT_NV12 139 
#define  DRM_FORMAT_RGB565 138 
#define  DRM_FORMAT_RGB888 137 
#define  DRM_FORMAT_RGBA4444 136 
#define  DRM_FORMAT_RGBA8888 135 
#define  DRM_FORMAT_RGBX4444 134 
#define  DRM_FORMAT_RGBX8888 133 
#define  DRM_FORMAT_UYVY 132 
#define  DRM_FORMAT_XRGB1555 131 
#define  DRM_FORMAT_XRGB4444 130 
#define  DRM_FORMAT_XRGB8888 129 
#define  DRM_FORMAT_YUYV 128 

__attribute__((used)) static int color_mode_to_bpp(u32 fourcc)
{
	switch (fourcc) {
	case DRM_FORMAT_NV12:
		return 8;
	case DRM_FORMAT_RGBX4444:
	case DRM_FORMAT_RGB565:
	case DRM_FORMAT_ARGB4444:
	case DRM_FORMAT_YUYV:
	case DRM_FORMAT_UYVY:
	case DRM_FORMAT_RGBA4444:
	case DRM_FORMAT_XRGB4444:
	case DRM_FORMAT_ARGB1555:
	case DRM_FORMAT_XRGB1555:
		return 16;
	case DRM_FORMAT_RGB888:
		return 24;
	case DRM_FORMAT_XRGB8888:
	case DRM_FORMAT_ARGB8888:
	case DRM_FORMAT_RGBA8888:
	case DRM_FORMAT_RGBX8888:
		return 32;
	default:
		BUG();
		return 0;
	}
}