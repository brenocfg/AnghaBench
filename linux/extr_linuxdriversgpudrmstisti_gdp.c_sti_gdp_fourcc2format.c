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
#define  DRM_FORMAT_ABGR8888 135 
#define  DRM_FORMAT_ARGB1555 134 
#define  DRM_FORMAT_ARGB4444 133 
#define  DRM_FORMAT_ARGB8888 132 
#define  DRM_FORMAT_RGB565 131 
#define  DRM_FORMAT_RGB888 130 
#define  DRM_FORMAT_XBGR8888 129 
#define  DRM_FORMAT_XRGB8888 128 
 int GDP_ABGR8888 ; 
 int GDP_ARGB1555 ; 
 int GDP_ARGB4444 ; 
 int GDP_ARGB8888 ; 
 int GDP_RGB565 ; 
 int GDP_RGB888 ; 
 int GDP_RGB888_32 ; 
 int GDP_XBGR8888 ; 

__attribute__((used)) static int sti_gdp_fourcc2format(int fourcc)
{
	switch (fourcc) {
	case DRM_FORMAT_XRGB8888:
		return GDP_RGB888_32;
	case DRM_FORMAT_XBGR8888:
		return GDP_XBGR8888;
	case DRM_FORMAT_ARGB8888:
		return GDP_ARGB8888;
	case DRM_FORMAT_ABGR8888:
		return GDP_ABGR8888;
	case DRM_FORMAT_ARGB4444:
		return GDP_ARGB4444;
	case DRM_FORMAT_ARGB1555:
		return GDP_ARGB1555;
	case DRM_FORMAT_RGB565:
		return GDP_RGB565;
	case DRM_FORMAT_RGB888:
		return GDP_RGB888;
	}
	return -1;
}