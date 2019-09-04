#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  src; } ;
struct intel_plane_state {TYPE_1__ base; } ;
struct drm_plane_state {int /*<<< orphan*/  rotation; struct drm_framebuffer* fb; } ;
struct drm_framebuffer {scalar_t__ modifier; TYPE_2__* format; } ;
struct TYPE_4__ {scalar_t__ format; int* cpp; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 scalar_t__ DRM_FORMAT_NV12 ; 
 scalar_t__ I915_FORMAT_MOD_Y_TILED ; 
 scalar_t__ I915_FORMAT_MOD_Y_TILED_CCS ; 
 scalar_t__ I915_FORMAT_MOD_Yf_TILED ; 
 scalar_t__ I915_FORMAT_MOD_Yf_TILED_CCS ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 scalar_t__ WARN_ON (int) ; 
 int drm_rect_height (int /*<<< orphan*/ *) ; 
 int drm_rect_width (int /*<<< orphan*/ *) ; 
 scalar_t__ drm_rotation_90_or_270 (int /*<<< orphan*/ ) ; 
 struct intel_plane_state* to_intel_plane_state (struct drm_plane_state const*) ; 

__attribute__((used)) static uint16_t
skl_ddb_min_alloc(const struct drm_plane_state *pstate, const int plane)
{
	struct drm_framebuffer *fb = pstate->fb;
	struct intel_plane_state *intel_pstate = to_intel_plane_state(pstate);
	uint32_t src_w, src_h;
	uint32_t min_scanlines = 8;
	uint8_t plane_bpp;

	if (WARN_ON(!fb))
		return 0;

	/* For packed formats, and uv-plane, return 0 */
	if (plane == 1 && fb->format->format != DRM_FORMAT_NV12)
		return 0;

	/* For Non Y-tile return 8-blocks */
	if (fb->modifier != I915_FORMAT_MOD_Y_TILED &&
	    fb->modifier != I915_FORMAT_MOD_Yf_TILED &&
	    fb->modifier != I915_FORMAT_MOD_Y_TILED_CCS &&
	    fb->modifier != I915_FORMAT_MOD_Yf_TILED_CCS)
		return 8;

	/*
	 * Src coordinates are already rotated by 270 degrees for
	 * the 90/270 degree plane rotation cases (to match the
	 * GTT mapping), hence no need to account for rotation here.
	 */
	src_w = drm_rect_width(&intel_pstate->base.src) >> 16;
	src_h = drm_rect_height(&intel_pstate->base.src) >> 16;

	/* Halve UV plane width and height for NV12 */
	if (plane == 1) {
		src_w /= 2;
		src_h /= 2;
	}

	plane_bpp = fb->format->cpp[plane];

	if (drm_rotation_90_or_270(pstate->rotation)) {
		switch (plane_bpp) {
		case 1:
			min_scanlines = 32;
			break;
		case 2:
			min_scanlines = 16;
			break;
		case 4:
			min_scanlines = 8;
			break;
		case 8:
			min_scanlines = 4;
			break;
		default:
			WARN(1, "Unsupported pixel depth %u for rotation",
			     plane_bpp);
			min_scanlines = 32;
		}
	}

	return DIV_ROUND_UP((4 * src_w * plane_bpp), 512) * min_scanlines/4 + 3;
}