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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
#define  DRM_FORMAT_RGB565 131 
#define  DRM_FORMAT_XBGR8888 130 
#define  DRM_FORMAT_XRGB1555 129 
#define  DRM_FORMAT_XRGB8888 128 
 int /*<<< orphan*/  IS_G4X (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_GEN (struct drm_i915_private*,int) ; 

__attribute__((used)) static bool pixel_format_is_valid(struct drm_i915_private *dev_priv,
				  u32 pixel_format)
{
	switch (pixel_format) {
	case DRM_FORMAT_XRGB8888:
	case DRM_FORMAT_XBGR8888:
		return true;
	case DRM_FORMAT_XRGB1555:
	case DRM_FORMAT_RGB565:
		/* 16bpp not supported on gen2 */
		if (IS_GEN(dev_priv, 2))
			return false;
		/* WaFbcOnly1to1Ratio:ctg */
		if (IS_G4X(dev_priv))
			return false;
		return true;
	default:
		return false;
	}
}