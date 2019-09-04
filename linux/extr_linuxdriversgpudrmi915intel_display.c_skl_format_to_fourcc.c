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
 int DRM_FORMAT_ABGR8888 ; 
 int DRM_FORMAT_ARGB8888 ; 
 int DRM_FORMAT_NV12 ; 
 int DRM_FORMAT_RGB565 ; 
 int DRM_FORMAT_XBGR2101010 ; 
 int DRM_FORMAT_XBGR8888 ; 
 int DRM_FORMAT_XRGB2101010 ; 
 int DRM_FORMAT_XRGB8888 ; 
#define  PLANE_CTL_FORMAT_NV12 131 
#define  PLANE_CTL_FORMAT_RGB_565 130 
#define  PLANE_CTL_FORMAT_XRGB_2101010 129 
#define  PLANE_CTL_FORMAT_XRGB_8888 128 

int skl_format_to_fourcc(int format, bool rgb_order, bool alpha)
{
	switch (format) {
	case PLANE_CTL_FORMAT_RGB_565:
		return DRM_FORMAT_RGB565;
	case PLANE_CTL_FORMAT_NV12:
		return DRM_FORMAT_NV12;
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
	}
}