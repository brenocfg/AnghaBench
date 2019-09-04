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
#define  DRM_FORMAT_ARGB1555 135 
#define  DRM_FORMAT_ARGB4444 134 
#define  DRM_FORMAT_ARGB8888 133 
#define  DRM_FORMAT_RGB565 132 
#define  DRM_FORMAT_RGB888 131 
#define  DRM_FORMAT_RGBA4444 130 
#define  DRM_FORMAT_RGBA5551 129 
#define  DRM_FORMAT_XRGB8888 128 
 int EINVAL ; 
 int SUN4I_BACKEND_LAY_FBFMT_ARGB1555 ; 
 int SUN4I_BACKEND_LAY_FBFMT_ARGB4444 ; 
 int SUN4I_BACKEND_LAY_FBFMT_ARGB8888 ; 
 int SUN4I_BACKEND_LAY_FBFMT_RGB565 ; 
 int SUN4I_BACKEND_LAY_FBFMT_RGB888 ; 
 int SUN4I_BACKEND_LAY_FBFMT_RGBA4444 ; 
 int SUN4I_BACKEND_LAY_FBFMT_RGBA5551 ; 
 int SUN4I_BACKEND_LAY_FBFMT_XRGB8888 ; 

__attribute__((used)) static int sun4i_backend_drm_format_to_layer(u32 format, u32 *mode)
{
	switch (format) {
	case DRM_FORMAT_ARGB8888:
		*mode = SUN4I_BACKEND_LAY_FBFMT_ARGB8888;
		break;

	case DRM_FORMAT_ARGB4444:
		*mode = SUN4I_BACKEND_LAY_FBFMT_ARGB4444;
		break;

	case DRM_FORMAT_ARGB1555:
		*mode = SUN4I_BACKEND_LAY_FBFMT_ARGB1555;
		break;

	case DRM_FORMAT_RGBA5551:
		*mode = SUN4I_BACKEND_LAY_FBFMT_RGBA5551;
		break;

	case DRM_FORMAT_RGBA4444:
		*mode = SUN4I_BACKEND_LAY_FBFMT_RGBA4444;
		break;

	case DRM_FORMAT_XRGB8888:
		*mode = SUN4I_BACKEND_LAY_FBFMT_XRGB8888;
		break;

	case DRM_FORMAT_RGB888:
		*mode = SUN4I_BACKEND_LAY_FBFMT_RGB888;
		break;

	case DRM_FORMAT_RGB565:
		*mode = SUN4I_BACKEND_LAY_FBFMT_RGB565;
		break;

	default:
		return -EINVAL;
	}

	return 0;
}