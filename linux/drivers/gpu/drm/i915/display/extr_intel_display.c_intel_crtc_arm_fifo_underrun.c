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
struct intel_crtc_state {scalar_t__ has_pch_encoder; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  IS_GEN (struct drm_i915_private*,int) ; 
 int intel_crtc_pch_transcoder (struct intel_crtc*) ; 
 int /*<<< orphan*/  intel_set_cpu_fifo_underrun_reporting (struct drm_i915_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_set_pch_fifo_underrun_reporting (struct drm_i915_private*,int,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

void intel_crtc_arm_fifo_underrun(struct intel_crtc *crtc,
				  struct intel_crtc_state *crtc_state)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);

	if (!IS_GEN(dev_priv, 2))
		intel_set_cpu_fifo_underrun_reporting(dev_priv, crtc->pipe, true);

	if (crtc_state->has_pch_encoder) {
		enum pipe pch_transcoder =
			intel_crtc_pch_transcoder(crtc);

		intel_set_pch_fifo_underrun_reporting(dev_priv, pch_transcoder, true);
	}
}