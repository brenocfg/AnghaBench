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
struct TYPE_5__ {int /*<<< orphan*/  crtc_clock; } ;
struct TYPE_6__ {TYPE_2__ adjusted_mode; TYPE_1__* crtc; } ;
struct intel_crtc_state {int /*<<< orphan*/  pixel_rate; TYPE_3__ base; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ HAS_GMCH (struct drm_i915_private*) ; 
 int /*<<< orphan*/  ilk_pipe_pixel_rate (struct intel_crtc_state*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_crtc_compute_pixel_rate(struct intel_crtc_state *crtc_state)
{
	struct drm_i915_private *dev_priv = to_i915(crtc_state->base.crtc->dev);

	if (HAS_GMCH(dev_priv))
		/* FIXME calculate proper pipe pixel rate for GMCH pfit */
		crtc_state->pixel_rate =
			crtc_state->base.adjusted_mode.crtc_clock;
	else
		crtc_state->pixel_rate =
			ilk_pipe_pixel_rate(crtc_state);
}