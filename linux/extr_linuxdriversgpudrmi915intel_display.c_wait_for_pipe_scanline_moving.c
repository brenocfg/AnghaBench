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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int pipe; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  onoff (int) ; 
 int /*<<< orphan*/  pipe_name (int) ; 
 int pipe_scanline_is_moving (struct drm_i915_private*,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 scalar_t__ wait_for (int,int) ; 

__attribute__((used)) static void wait_for_pipe_scanline_moving(struct intel_crtc *crtc, bool state)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	enum pipe pipe = crtc->pipe;

	/* Wait for the display line to settle/start moving */
	if (wait_for(pipe_scanline_is_moving(dev_priv, pipe) == state, 100))
		DRM_ERROR("pipe %c scanline %s wait timed out\n",
			  pipe_name(pipe), onoff(state));
}