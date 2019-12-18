#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ quirk_addfb_prefer_xbgr_30bpp; scalar_t__ quirk_addfb_prefer_host_byte_order; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 scalar_t__ DRM_FORMAT_ARGB8888 ; 
 scalar_t__ DRM_FORMAT_HOST_ARGB8888 ; 
 scalar_t__ DRM_FORMAT_HOST_RGB565 ; 
 scalar_t__ DRM_FORMAT_HOST_XRGB1555 ; 
 scalar_t__ DRM_FORMAT_HOST_XRGB8888 ; 
 scalar_t__ DRM_FORMAT_RGB565 ; 
 scalar_t__ DRM_FORMAT_XBGR2101010 ; 
 scalar_t__ DRM_FORMAT_XRGB1555 ; 
 scalar_t__ DRM_FORMAT_XRGB2101010 ; 
 scalar_t__ DRM_FORMAT_XRGB8888 ; 
 scalar_t__ drm_mode_legacy_fb_format (scalar_t__,scalar_t__) ; 

uint32_t drm_driver_legacy_fb_format(struct drm_device *dev,
				     uint32_t bpp, uint32_t depth)
{
	uint32_t fmt = drm_mode_legacy_fb_format(bpp, depth);

	if (dev->mode_config.quirk_addfb_prefer_host_byte_order) {
		if (fmt == DRM_FORMAT_XRGB8888)
			fmt = DRM_FORMAT_HOST_XRGB8888;
		if (fmt == DRM_FORMAT_ARGB8888)
			fmt = DRM_FORMAT_HOST_ARGB8888;
		if (fmt == DRM_FORMAT_RGB565)
			fmt = DRM_FORMAT_HOST_RGB565;
		if (fmt == DRM_FORMAT_XRGB1555)
			fmt = DRM_FORMAT_HOST_XRGB1555;
	}

	if (dev->mode_config.quirk_addfb_prefer_xbgr_30bpp &&
	    fmt == DRM_FORMAT_XRGB2101010)
		fmt = DRM_FORMAT_XBGR2101010;

	return fmt;
}