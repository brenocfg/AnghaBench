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

/* Variables and functions */
 int DRM_FORMAT_ABGR16161616F ; 
 int DRM_FORMAT_ABGR8888 ; 
 int DRM_FORMAT_ARGB16161616F ; 
 int DRM_FORMAT_ARGB8888 ; 
 int DRM_FORMAT_NV12 ; 
 int DRM_FORMAT_P010 ; 
 int DRM_FORMAT_P012 ; 
 int DRM_FORMAT_P016 ; 
 int DRM_FORMAT_RGB565 ; 
 int DRM_FORMAT_XBGR16161616F ; 
 int DRM_FORMAT_XBGR2101010 ; 
 int DRM_FORMAT_XBGR8888 ; 
 int DRM_FORMAT_XRGB16161616F ; 
 int DRM_FORMAT_XRGB2101010 ; 
 int DRM_FORMAT_XRGB8888 ; 
 int DRM_FORMAT_XVYU12_16161616 ; 
 int DRM_FORMAT_XVYU16161616 ; 
 int DRM_FORMAT_XVYU2101010 ; 
 int DRM_FORMAT_Y210 ; 
 int DRM_FORMAT_Y212 ; 
 int DRM_FORMAT_Y216 ; 
#define  PLANE_CTL_FORMAT_NV12 141 
#define  PLANE_CTL_FORMAT_P010 140 
#define  PLANE_CTL_FORMAT_P012 139 
#define  PLANE_CTL_FORMAT_P016 138 
#define  PLANE_CTL_FORMAT_RGB_565 137 
#define  PLANE_CTL_FORMAT_XRGB_16161616F 136 
#define  PLANE_CTL_FORMAT_XRGB_2101010 135 
#define  PLANE_CTL_FORMAT_XRGB_8888 134 
#define  PLANE_CTL_FORMAT_Y210 133 
#define  PLANE_CTL_FORMAT_Y212 132 
#define  PLANE_CTL_FORMAT_Y216 131 
#define  PLANE_CTL_FORMAT_Y410 130 
#define  PLANE_CTL_FORMAT_Y412 129 
#define  PLANE_CTL_FORMAT_Y416 128 

int skl_format_to_fourcc(int format, bool rgb_order, bool alpha)
{
	switch (format) {
	case PLANE_CTL_FORMAT_RGB_565:
		return DRM_FORMAT_RGB565;
	case PLANE_CTL_FORMAT_NV12:
		return DRM_FORMAT_NV12;
	case PLANE_CTL_FORMAT_P010:
		return DRM_FORMAT_P010;
	case PLANE_CTL_FORMAT_P012:
		return DRM_FORMAT_P012;
	case PLANE_CTL_FORMAT_P016:
		return DRM_FORMAT_P016;
	case PLANE_CTL_FORMAT_Y210:
		return DRM_FORMAT_Y210;
	case PLANE_CTL_FORMAT_Y212:
		return DRM_FORMAT_Y212;
	case PLANE_CTL_FORMAT_Y216:
		return DRM_FORMAT_Y216;
	case PLANE_CTL_FORMAT_Y410:
		return DRM_FORMAT_XVYU2101010;
	case PLANE_CTL_FORMAT_Y412:
		return DRM_FORMAT_XVYU12_16161616;
	case PLANE_CTL_FORMAT_Y416:
		return DRM_FORMAT_XVYU16161616;
	default:
	case PLANE_CTL_FORMAT_XRGB_8888:
		if (rgb_order) {
			if (alpha)
				return DRM_FORMAT_ABGR8888;
			else
				return DRM_FORMAT_XBGR8888;
		} else {
			if (alpha)
				return DRM_FORMAT_ARGB8888;
			else
				return DRM_FORMAT_XRGB8888;
		}
	case PLANE_CTL_FORMAT_XRGB_2101010:
		if (rgb_order)
			return DRM_FORMAT_XBGR2101010;
		else
			return DRM_FORMAT_XRGB2101010;
	case PLANE_CTL_FORMAT_XRGB_16161616F:
		if (rgb_order) {
			if (alpha)
				return DRM_FORMAT_ABGR16161616F;
			else
				return DRM_FORMAT_XBGR16161616F;
		} else {
			if (alpha)
				return DRM_FORMAT_ARGB16161616F;
			else
				return DRM_FORMAT_XRGB16161616F;
		}
	}
}