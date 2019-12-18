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

/* Variables and functions */
 int DRM_FORMAT_ARGB8888 ; 
 int DRM_FORMAT_C8 ; 
 int DRM_FORMAT_INVALID ; 
 int DRM_FORMAT_RGB565 ; 
 int DRM_FORMAT_RGB888 ; 
 int DRM_FORMAT_XRGB1555 ; 
 int DRM_FORMAT_XRGB2101010 ; 
 int DRM_FORMAT_XRGB8888 ; 

uint32_t drm_mode_legacy_fb_format(uint32_t bpp, uint32_t depth)
{
	uint32_t fmt = DRM_FORMAT_INVALID;

	switch (bpp) {
	case 8:
		if (depth == 8)
			fmt = DRM_FORMAT_C8;
		break;

	case 16:
		switch (depth) {
		case 15:
			fmt = DRM_FORMAT_XRGB1555;
			break;
		case 16:
			fmt = DRM_FORMAT_RGB565;
			break;
		default:
			break;
		}
		break;

	case 24:
		if (depth == 24)
			fmt = DRM_FORMAT_RGB888;
		break;

	case 32:
		switch (depth) {
		case 24:
			fmt = DRM_FORMAT_XRGB8888;
			break;
		case 30:
			fmt = DRM_FORMAT_XRGB2101010;
			break;
		case 32:
			fmt = DRM_FORMAT_ARGB8888;
			break;
		default:
			break;
		}
		break;

	default:
		break;
	}

	return fmt;
}