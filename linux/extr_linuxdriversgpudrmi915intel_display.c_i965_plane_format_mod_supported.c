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
typedef  int u64 ;
typedef  int u32 ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
#define  DRM_FORMAT_C8 135 
#define  DRM_FORMAT_MOD_LINEAR 134 
#define  DRM_FORMAT_RGB565 133 
#define  DRM_FORMAT_XBGR2101010 132 
#define  DRM_FORMAT_XBGR8888 131 
#define  DRM_FORMAT_XRGB2101010 130 
#define  DRM_FORMAT_XRGB8888 129 
#define  I915_FORMAT_MOD_X_TILED 128 

__attribute__((used)) static bool i965_plane_format_mod_supported(struct drm_plane *_plane,
					    u32 format, u64 modifier)
{
	switch (modifier) {
	case DRM_FORMAT_MOD_LINEAR:
	case I915_FORMAT_MOD_X_TILED:
		break;
	default:
		return false;
	}

	switch (format) {
	case DRM_FORMAT_C8:
	case DRM_FORMAT_RGB565:
	case DRM_FORMAT_XRGB8888:
	case DRM_FORMAT_XBGR8888:
	case DRM_FORMAT_XRGB2101010:
	case DRM_FORMAT_XBGR2101010:
		return modifier == DRM_FORMAT_MOD_LINEAR ||
			modifier == I915_FORMAT_MOD_X_TILED;
	default:
		return false;
	}
}