#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int rotation; struct drm_framebuffer* fb; int /*<<< orphan*/  plane; } ;
struct intel_plane_state {TYPE_2__ base; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct intel_plane {TYPE_1__ base; } ;
struct TYPE_9__ {int flags; } ;
struct TYPE_10__ {TYPE_4__ adjusted_mode; scalar_t__ enable; } ;
struct intel_crtc_state {TYPE_5__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_framebuffer {scalar_t__ modifier; TYPE_3__* format; } ;
struct drm_format_name_buf {int dummy; } ;
struct TYPE_8__ {int format; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
#define  DRM_FORMAT_ABGR16161616F 138 
#define  DRM_FORMAT_ARGB16161616F 137 
#define  DRM_FORMAT_C8 136 
 scalar_t__ DRM_FORMAT_MOD_LINEAR ; 
#define  DRM_FORMAT_RGB565 135 
#define  DRM_FORMAT_XBGR16161616F 134 
#define  DRM_FORMAT_XRGB16161616F 133 
#define  DRM_FORMAT_XVYU12_16161616 132 
#define  DRM_FORMAT_XVYU16161616 131 
#define  DRM_FORMAT_Y210 130 
#define  DRM_FORMAT_Y212 129 
#define  DRM_FORMAT_Y216 128 
 int DRM_MODE_FLAG_INTERLACE ; 
 unsigned int DRM_MODE_REFLECT_X ; 
 unsigned int DRM_MODE_ROTATE_0 ; 
 unsigned int DRM_MODE_ROTATE_180 ; 
 int EINVAL ; 
 scalar_t__ I915_FORMAT_MOD_Y_TILED ; 
 scalar_t__ I915_FORMAT_MOD_Y_TILED_CCS ; 
 scalar_t__ I915_FORMAT_MOD_Yf_TILED ; 
 scalar_t__ I915_FORMAT_MOD_Yf_TILED_CCS ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  drm_get_format_name (int,struct drm_format_name_buf*) ; 
 scalar_t__ drm_rotation_90_or_270 (unsigned int) ; 
 scalar_t__ is_ccs_modifier (scalar_t__) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_plane* to_intel_plane (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skl_plane_check_fb(const struct intel_crtc_state *crtc_state,
			      const struct intel_plane_state *plane_state)
{
	struct intel_plane *plane = to_intel_plane(plane_state->base.plane);
	struct drm_i915_private *dev_priv = to_i915(plane->base.dev);
	const struct drm_framebuffer *fb = plane_state->base.fb;
	unsigned int rotation = plane_state->base.rotation;
	struct drm_format_name_buf format_name;

	if (!fb)
		return 0;

	if (rotation & ~(DRM_MODE_ROTATE_0 | DRM_MODE_ROTATE_180) &&
	    is_ccs_modifier(fb->modifier)) {
		DRM_DEBUG_KMS("RC support only with 0/180 degree rotation (%x)\n",
			      rotation);
		return -EINVAL;
	}

	if (rotation & DRM_MODE_REFLECT_X &&
	    fb->modifier == DRM_FORMAT_MOD_LINEAR) {
		DRM_DEBUG_KMS("horizontal flip is not supported with linear surface formats\n");
		return -EINVAL;
	}

	if (drm_rotation_90_or_270(rotation)) {
		if (fb->modifier != I915_FORMAT_MOD_Y_TILED &&
		    fb->modifier != I915_FORMAT_MOD_Yf_TILED) {
			DRM_DEBUG_KMS("Y/Yf tiling required for 90/270!\n");
			return -EINVAL;
		}

		/*
		 * 90/270 is not allowed with RGB64 16:16:16:16 and
		 * Indexed 8-bit. RGB 16-bit 5:6:5 is allowed gen11 onwards.
		 */
		switch (fb->format->format) {
		case DRM_FORMAT_RGB565:
			if (INTEL_GEN(dev_priv) >= 11)
				break;
			/* fall through */
		case DRM_FORMAT_C8:
		case DRM_FORMAT_XRGB16161616F:
		case DRM_FORMAT_XBGR16161616F:
		case DRM_FORMAT_ARGB16161616F:
		case DRM_FORMAT_ABGR16161616F:
		case DRM_FORMAT_Y210:
		case DRM_FORMAT_Y212:
		case DRM_FORMAT_Y216:
		case DRM_FORMAT_XVYU12_16161616:
		case DRM_FORMAT_XVYU16161616:
			DRM_DEBUG_KMS("Unsupported pixel format %s for 90/270!\n",
				      drm_get_format_name(fb->format->format,
							  &format_name));
			return -EINVAL;
		default:
			break;
		}
	}

	/* Y-tiling is not supported in IF-ID Interlace mode */
	if (crtc_state->base.enable &&
	    crtc_state->base.adjusted_mode.flags & DRM_MODE_FLAG_INTERLACE &&
	    (fb->modifier == I915_FORMAT_MOD_Y_TILED ||
	     fb->modifier == I915_FORMAT_MOD_Yf_TILED ||
	     fb->modifier == I915_FORMAT_MOD_Y_TILED_CCS ||
	     fb->modifier == I915_FORMAT_MOD_Yf_TILED_CCS)) {
		DRM_DEBUG_KMS("Y/Yf tiling not supported in IF-ID mode\n");
		return -EINVAL;
	}

	return 0;
}