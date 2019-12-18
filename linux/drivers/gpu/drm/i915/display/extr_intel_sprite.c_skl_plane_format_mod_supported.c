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
struct intel_plane {int /*<<< orphan*/  has_ccs; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
#define  DRM_FORMAT_ABGR16161616F 159 
#define  DRM_FORMAT_ABGR8888 158 
#define  DRM_FORMAT_ARGB16161616F 157 
#define  DRM_FORMAT_ARGB8888 156 
#define  DRM_FORMAT_C8 155 
#define  DRM_FORMAT_MOD_LINEAR 154 
#define  DRM_FORMAT_NV12 153 
#define  DRM_FORMAT_P010 152 
#define  DRM_FORMAT_P012 151 
#define  DRM_FORMAT_P016 150 
#define  DRM_FORMAT_RGB565 149 
#define  DRM_FORMAT_UYVY 148 
#define  DRM_FORMAT_VYUY 147 
#define  DRM_FORMAT_XBGR16161616F 146 
#define  DRM_FORMAT_XBGR2101010 145 
#define  DRM_FORMAT_XBGR8888 144 
#define  DRM_FORMAT_XRGB16161616F 143 
#define  DRM_FORMAT_XRGB2101010 142 
#define  DRM_FORMAT_XRGB8888 141 
#define  DRM_FORMAT_XVYU12_16161616 140 
#define  DRM_FORMAT_XVYU16161616 139 
#define  DRM_FORMAT_XVYU2101010 138 
#define  DRM_FORMAT_Y210 137 
#define  DRM_FORMAT_Y212 136 
#define  DRM_FORMAT_Y216 135 
#define  DRM_FORMAT_YUYV 134 
#define  DRM_FORMAT_YVYU 133 
#define  I915_FORMAT_MOD_X_TILED 132 
#define  I915_FORMAT_MOD_Y_TILED 131 
#define  I915_FORMAT_MOD_Y_TILED_CCS 130 
#define  I915_FORMAT_MOD_Yf_TILED 129 
#define  I915_FORMAT_MOD_Yf_TILED_CCS 128 
 int /*<<< orphan*/  is_ccs_modifier (int) ; 
 struct intel_plane* to_intel_plane (struct drm_plane*) ; 

__attribute__((used)) static bool skl_plane_format_mod_supported(struct drm_plane *_plane,
					   u32 format, u64 modifier)
{
	struct intel_plane *plane = to_intel_plane(_plane);

	switch (modifier) {
	case DRM_FORMAT_MOD_LINEAR:
	case I915_FORMAT_MOD_X_TILED:
	case I915_FORMAT_MOD_Y_TILED:
	case I915_FORMAT_MOD_Yf_TILED:
		break;
	case I915_FORMAT_MOD_Y_TILED_CCS:
	case I915_FORMAT_MOD_Yf_TILED_CCS:
		if (!plane->has_ccs)
			return false;
		break;
	default:
		return false;
	}

	switch (format) {
	case DRM_FORMAT_XRGB8888:
	case DRM_FORMAT_XBGR8888:
	case DRM_FORMAT_ARGB8888:
	case DRM_FORMAT_ABGR8888:
		if (is_ccs_modifier(modifier))
			return true;
		/* fall through */
	case DRM_FORMAT_RGB565:
	case DRM_FORMAT_XRGB2101010:
	case DRM_FORMAT_XBGR2101010:
	case DRM_FORMAT_YUYV:
	case DRM_FORMAT_YVYU:
	case DRM_FORMAT_UYVY:
	case DRM_FORMAT_VYUY:
	case DRM_FORMAT_NV12:
	case DRM_FORMAT_P010:
	case DRM_FORMAT_P012:
	case DRM_FORMAT_P016:
	case DRM_FORMAT_XVYU2101010:
		if (modifier == I915_FORMAT_MOD_Yf_TILED)
			return true;
		/* fall through */
	case DRM_FORMAT_C8:
	case DRM_FORMAT_XBGR16161616F:
	case DRM_FORMAT_ABGR16161616F:
	case DRM_FORMAT_XRGB16161616F:
	case DRM_FORMAT_ARGB16161616F:
	case DRM_FORMAT_Y210:
	case DRM_FORMAT_Y212:
	case DRM_FORMAT_Y216:
	case DRM_FORMAT_XVYU12_16161616:
	case DRM_FORMAT_XVYU16161616:
		if (modifier == DRM_FORMAT_MOD_LINEAR ||
		    modifier == I915_FORMAT_MOD_X_TILED ||
		    modifier == I915_FORMAT_MOD_Y_TILED)
			return true;
		/* fall through */
	default:
		return false;
	}
}