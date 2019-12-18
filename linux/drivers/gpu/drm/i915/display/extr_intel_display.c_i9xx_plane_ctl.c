#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {unsigned int rotation; struct drm_framebuffer* fb; TYPE_1__* plane; } ;
struct intel_plane_state {TYPE_2__ base; } ;
struct intel_crtc_state {int dummy; } ;
struct drm_i915_private {int dummy; } ;
struct drm_framebuffer {scalar_t__ modifier; TYPE_3__* format; } ;
struct TYPE_6__ {int format; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY_PLANE_ENABLE ; 
 int /*<<< orphan*/  DISPPLANE_8BPP ; 
 int /*<<< orphan*/  DISPPLANE_BGRX101010 ; 
 int /*<<< orphan*/  DISPPLANE_BGRX555 ; 
 int /*<<< orphan*/  DISPPLANE_BGRX565 ; 
 int /*<<< orphan*/  DISPPLANE_BGRX888 ; 
 int /*<<< orphan*/  DISPPLANE_MIRROR ; 
 int /*<<< orphan*/  DISPPLANE_RGBX101010 ; 
 int /*<<< orphan*/  DISPPLANE_RGBX888 ; 
 int /*<<< orphan*/  DISPPLANE_ROTATE_180 ; 
 int /*<<< orphan*/  DISPPLANE_TILED ; 
 int /*<<< orphan*/  DISPPLANE_TRICKLE_FEED_DISABLE ; 
#define  DRM_FORMAT_C8 134 
#define  DRM_FORMAT_RGB565 133 
#define  DRM_FORMAT_XBGR2101010 132 
#define  DRM_FORMAT_XBGR8888 131 
#define  DRM_FORMAT_XRGB1555 130 
#define  DRM_FORMAT_XRGB2101010 129 
#define  DRM_FORMAT_XRGB8888 128 
 unsigned int DRM_MODE_REFLECT_X ; 
 unsigned int DRM_MODE_ROTATE_180 ; 
 scalar_t__ I915_FORMAT_MOD_X_TILED ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_G4X (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_IVYBRIDGE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 i9xx_plane_ctl(const struct intel_crtc_state *crtc_state,
			  const struct intel_plane_state *plane_state)
{
	struct drm_i915_private *dev_priv =
		to_i915(plane_state->base.plane->dev);
	const struct drm_framebuffer *fb = plane_state->base.fb;
	unsigned int rotation = plane_state->base.rotation;
	u32 dspcntr;

	dspcntr = DISPLAY_PLANE_ENABLE;

	if (IS_G4X(dev_priv) || IS_GEN(dev_priv, 5) ||
	    IS_GEN(dev_priv, 6) || IS_IVYBRIDGE(dev_priv))
		dspcntr |= DISPPLANE_TRICKLE_FEED_DISABLE;

	switch (fb->format->format) {
	case DRM_FORMAT_C8:
		dspcntr |= DISPPLANE_8BPP;
		break;
	case DRM_FORMAT_XRGB1555:
		dspcntr |= DISPPLANE_BGRX555;
		break;
	case DRM_FORMAT_RGB565:
		dspcntr |= DISPPLANE_BGRX565;
		break;
	case DRM_FORMAT_XRGB8888:
		dspcntr |= DISPPLANE_BGRX888;
		break;
	case DRM_FORMAT_XBGR8888:
		dspcntr |= DISPPLANE_RGBX888;
		break;
	case DRM_FORMAT_XRGB2101010:
		dspcntr |= DISPPLANE_BGRX101010;
		break;
	case DRM_FORMAT_XBGR2101010:
		dspcntr |= DISPPLANE_RGBX101010;
		break;
	default:
		MISSING_CASE(fb->format->format);
		return 0;
	}

	if (INTEL_GEN(dev_priv) >= 4 &&
	    fb->modifier == I915_FORMAT_MOD_X_TILED)
		dspcntr |= DISPPLANE_TILED;

	if (rotation & DRM_MODE_ROTATE_180)
		dspcntr |= DISPPLANE_ROTATE_180;

	if (rotation & DRM_MODE_REFLECT_X)
		dspcntr |= DISPPLANE_MIRROR;

	return dspcntr;
}