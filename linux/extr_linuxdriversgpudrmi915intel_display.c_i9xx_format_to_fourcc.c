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
#define  DISPPLANE_8BPP 134 
#define  DISPPLANE_BGRX101010 133 
#define  DISPPLANE_BGRX555 132 
#define  DISPPLANE_BGRX565 131 
#define  DISPPLANE_BGRX888 130 
#define  DISPPLANE_RGBX101010 129 
#define  DISPPLANE_RGBX888 128 
 int DRM_FORMAT_C8 ; 
 int DRM_FORMAT_RGB565 ; 
 int DRM_FORMAT_XBGR2101010 ; 
 int DRM_FORMAT_XBGR8888 ; 
 int DRM_FORMAT_XRGB1555 ; 
 int DRM_FORMAT_XRGB2101010 ; 
 int DRM_FORMAT_XRGB8888 ; 

__attribute__((used)) static int i9xx_format_to_fourcc(int format)
{
	switch (format) {
	case DISPPLANE_8BPP:
		return DRM_FORMAT_C8;
	case DISPPLANE_BGRX555:
		return DRM_FORMAT_XRGB1555;
	case DISPPLANE_BGRX565:
		return DRM_FORMAT_RGB565;
	default:
	case DISPPLANE_BGRX888:
		return DRM_FORMAT_XRGB8888;
	case DISPPLANE_RGBX888:
		return DRM_FORMAT_XBGR8888;
	case DISPPLANE_BGRX101010:
		return DRM_FORMAT_XRGB2101010;
	case DISPPLANE_RGBX101010:
		return DRM_FORMAT_XBGR2101010;
	}
}