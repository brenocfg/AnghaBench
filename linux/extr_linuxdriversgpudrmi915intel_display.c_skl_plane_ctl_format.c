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
typedef  int uint32_t ;
typedef  int u32 ;

/* Variables and functions */
#define  DRM_FORMAT_ABGR8888 140 
#define  DRM_FORMAT_ARGB8888 139 
#define  DRM_FORMAT_C8 138 
#define  DRM_FORMAT_NV12 137 
#define  DRM_FORMAT_RGB565 136 
#define  DRM_FORMAT_UYVY 135 
#define  DRM_FORMAT_VYUY 134 
#define  DRM_FORMAT_XBGR2101010 133 
#define  DRM_FORMAT_XBGR8888 132 
#define  DRM_FORMAT_XRGB2101010 131 
#define  DRM_FORMAT_XRGB8888 130 
#define  DRM_FORMAT_YUYV 129 
#define  DRM_FORMAT_YVYU 128 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int PLANE_CTL_FORMAT_INDEXED ; 
 int PLANE_CTL_FORMAT_NV12 ; 
 int PLANE_CTL_FORMAT_RGB_565 ; 
 int PLANE_CTL_FORMAT_XRGB_2101010 ; 
 int PLANE_CTL_FORMAT_XRGB_8888 ; 
 int PLANE_CTL_FORMAT_YUV422 ; 
 int PLANE_CTL_ORDER_RGBX ; 
 int PLANE_CTL_YUV422_UYVY ; 
 int PLANE_CTL_YUV422_VYUY ; 
 int PLANE_CTL_YUV422_YUYV ; 
 int PLANE_CTL_YUV422_YVYU ; 

__attribute__((used)) static u32 skl_plane_ctl_format(uint32_t pixel_format)
{
	switch (pixel_format) {
	case DRM_FORMAT_C8:
		return PLANE_CTL_FORMAT_INDEXED;
	case DRM_FORMAT_RGB565:
		return PLANE_CTL_FORMAT_RGB_565;
	case DRM_FORMAT_XBGR8888:
	case DRM_FORMAT_ABGR8888:
		return PLANE_CTL_FORMAT_XRGB_8888 | PLANE_CTL_ORDER_RGBX;
	case DRM_FORMAT_XRGB8888:
	case DRM_FORMAT_ARGB8888:
		return PLANE_CTL_FORMAT_XRGB_8888;
	case DRM_FORMAT_XRGB2101010:
		return PLANE_CTL_FORMAT_XRGB_2101010;
	case DRM_FORMAT_XBGR2101010:
		return PLANE_CTL_ORDER_RGBX | PLANE_CTL_FORMAT_XRGB_2101010;
	case DRM_FORMAT_YUYV:
		return PLANE_CTL_FORMAT_YUV422 | PLANE_CTL_YUV422_YUYV;
	case DRM_FORMAT_YVYU:
		return PLANE_CTL_FORMAT_YUV422 | PLANE_CTL_YUV422_YVYU;
	case DRM_FORMAT_UYVY:
		return PLANE_CTL_FORMAT_YUV422 | PLANE_CTL_YUV422_UYVY;
	case DRM_FORMAT_VYUY:
		return PLANE_CTL_FORMAT_YUV422 | PLANE_CTL_YUV422_VYUY;
	case DRM_FORMAT_NV12:
		return PLANE_CTL_FORMAT_NV12;
	default:
		MISSING_CASE(pixel_format);
	}

	return 0;
}