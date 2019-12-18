#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int crtc_w; scalar_t__ crtc_x; scalar_t__ visible; int /*<<< orphan*/  crtc_h; struct drm_framebuffer* fb; int /*<<< orphan*/  plane; } ;
struct intel_plane_state {int /*<<< orphan*/  ctl; TYPE_4__ base; TYPE_2__* color_plane; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct intel_plane {int pipe; TYPE_1__ base; } ;
struct intel_crtc_state {int dummy; } ;
struct drm_i915_private {int dummy; } ;
struct drm_framebuffer {int* pitches; TYPE_3__* format; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_7__ {int* cpp; } ;
struct TYPE_6__ {int stride; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int EINVAL ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 int PIPE_C ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  i9xx_cursor_ctl (struct intel_crtc_state*,struct intel_plane_state*) ; 
 int /*<<< orphan*/  i9xx_cursor_size_ok (struct intel_plane_state*) ; 
 int intel_check_cursor (struct intel_crtc_state*,struct intel_plane_state*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_plane* to_intel_plane (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i9xx_check_cursor(struct intel_crtc_state *crtc_state,
			     struct intel_plane_state *plane_state)
{
	struct intel_plane *plane = to_intel_plane(plane_state->base.plane);
	struct drm_i915_private *dev_priv = to_i915(plane->base.dev);
	const struct drm_framebuffer *fb = plane_state->base.fb;
	enum pipe pipe = plane->pipe;
	int ret;

	ret = intel_check_cursor(crtc_state, plane_state);
	if (ret)
		return ret;

	/* if we want to turn off the cursor ignore width and height */
	if (!fb)
		return 0;

	/* Check for which cursor types we support */
	if (!i9xx_cursor_size_ok(plane_state)) {
		DRM_DEBUG("Cursor dimension %dx%d not supported\n",
			  plane_state->base.crtc_w,
			  plane_state->base.crtc_h);
		return -EINVAL;
	}

	WARN_ON(plane_state->base.visible &&
		plane_state->color_plane[0].stride != fb->pitches[0]);

	if (fb->pitches[0] != plane_state->base.crtc_w * fb->format->cpp[0]) {
		DRM_DEBUG_KMS("Invalid cursor stride (%u) (cursor width %d)\n",
			      fb->pitches[0], plane_state->base.crtc_w);
		return -EINVAL;
	}

	/*
	 * There's something wrong with the cursor on CHV pipe C.
	 * If it straddles the left edge of the screen then
	 * moving it away from the edge or disabling it often
	 * results in a pipe underrun, and often that can lead to
	 * dead pipe (constant underrun reported, and it scans
	 * out just a solid color). To recover from that, the
	 * display power well must be turned off and on again.
	 * Refuse the put the cursor into that compromised position.
	 */
	if (IS_CHERRYVIEW(dev_priv) && pipe == PIPE_C &&
	    plane_state->base.visible && plane_state->base.crtc_x < 0) {
		DRM_DEBUG_KMS("CHV cursor C not allowed to straddle the left screen edge\n");
		return -EINVAL;
	}

	plane_state->ctl = i9xx_cursor_ctl(crtc_state, plane_state);

	return 0;
}