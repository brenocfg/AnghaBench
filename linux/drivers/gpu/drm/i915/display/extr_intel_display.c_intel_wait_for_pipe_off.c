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
struct TYPE_3__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {int cpu_transcoder; TYPE_1__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;

/* Variables and functions */
 int /*<<< orphan*/  I965_PIPECONF_ACTIVE ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PIPECONF (int) ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 scalar_t__ intel_de_wait_for_clear (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_wait_for_pipe_scanline_stopped (struct intel_crtc*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
intel_wait_for_pipe_off(const struct intel_crtc_state *old_crtc_state)
{
	struct intel_crtc *crtc = to_intel_crtc(old_crtc_state->base.crtc);
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);

	if (INTEL_GEN(dev_priv) >= 4) {
		enum transcoder cpu_transcoder = old_crtc_state->cpu_transcoder;
		i915_reg_t reg = PIPECONF(cpu_transcoder);

		/* Wait for the Pipe State to go off */
		if (intel_de_wait_for_clear(dev_priv, reg,
					    I965_PIPECONF_ACTIVE, 100))
			WARN(1, "pipe_off wait timed out\n");
	} else {
		intel_wait_for_pipe_scanline_stopped(crtc);
	}
}