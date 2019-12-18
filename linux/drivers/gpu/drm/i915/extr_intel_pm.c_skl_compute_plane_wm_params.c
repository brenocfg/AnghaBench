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
struct skl_wm_params {int dummy; } ;
struct TYPE_2__ {int crtc_w; int /*<<< orphan*/  rotation; int /*<<< orphan*/  src; struct drm_framebuffer* fb; int /*<<< orphan*/  plane; } ;
struct intel_plane_state {TYPE_1__ base; } ;
struct intel_plane {scalar_t__ id; } ;
struct intel_crtc_state {int dummy; } ;
struct drm_framebuffer {int /*<<< orphan*/  modifier; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 scalar_t__ PLANE_CURSOR ; 
 int drm_rect_width (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skl_adjusted_plane_pixel_rate (struct intel_crtc_state const*,struct intel_plane_state const*) ; 
 int skl_compute_wm_params (struct intel_crtc_state const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct skl_wm_params*,int) ; 
 struct intel_plane* to_intel_plane (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
skl_compute_plane_wm_params(const struct intel_crtc_state *crtc_state,
			    const struct intel_plane_state *plane_state,
			    struct skl_wm_params *wp, int color_plane)
{
	struct intel_plane *plane = to_intel_plane(plane_state->base.plane);
	const struct drm_framebuffer *fb = plane_state->base.fb;
	int width;

	if (plane->id == PLANE_CURSOR) {
		width = plane_state->base.crtc_w;
	} else {
		/*
		 * Src coordinates are already rotated by 270 degrees for
		 * the 90/270 degree plane rotation cases (to match the
		 * GTT mapping), hence no need to account for rotation here.
		 */
		width = drm_rect_width(&plane_state->base.src) >> 16;
	}

	return skl_compute_wm_params(crtc_state, width,
				     fb->format, fb->modifier,
				     plane_state->base.rotation,
				     skl_adjusted_plane_pixel_rate(crtc_state, plane_state),
				     wp, color_plane);
}