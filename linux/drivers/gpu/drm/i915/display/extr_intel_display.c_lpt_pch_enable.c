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
struct intel_atomic_state {int dummy; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;

/* Variables and functions */
 int /*<<< orphan*/  PIPE_A ; 
 int /*<<< orphan*/  assert_pch_transcoder_disabled (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ironlake_pch_transcoder_set_timings (struct intel_crtc_state const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpt_enable_pch_transcoder (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  lpt_program_iclkip (struct intel_crtc_state const*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lpt_pch_enable(const struct intel_atomic_state *state,
			   const struct intel_crtc_state *crtc_state)
{
	struct intel_crtc *crtc = to_intel_crtc(crtc_state->base.crtc);
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	enum transcoder cpu_transcoder = crtc_state->cpu_transcoder;

	assert_pch_transcoder_disabled(dev_priv, PIPE_A);

	lpt_program_iclkip(crtc_state);

	/* Set transcoder timing. */
	ironlake_pch_transcoder_set_timings(crtc_state, PIPE_A);

	lpt_enable_pch_transcoder(dev_priv, cpu_transcoder);
}