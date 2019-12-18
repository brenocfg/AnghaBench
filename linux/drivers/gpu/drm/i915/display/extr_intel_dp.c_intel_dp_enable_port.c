#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct intel_dp {int /*<<< orphan*/  output_reg; int /*<<< orphan*/  DP; } ;
struct intel_crtc_state {scalar_t__ has_audio; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_AUDIO_OUTPUT_ENABLE ; 
 int /*<<< orphan*/  DP_PORT_EN ; 
 int /*<<< orphan*/  DP_TRAINING_PATTERN_1 ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 struct drm_i915_private* dp_to_i915 (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_program_link_training_pattern (struct intel_dp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_dp_enable_port(struct intel_dp *intel_dp,
				 const struct intel_crtc_state *old_crtc_state)
{
	struct drm_i915_private *dev_priv = dp_to_i915(intel_dp);

	/* enable with pattern 1 (as per spec) */

	intel_dp_program_link_training_pattern(intel_dp, DP_TRAINING_PATTERN_1);

	/*
	 * Magic for VLV/CHV. We _must_ first set up the register
	 * without actually enabling the port, and then do another
	 * write to enable the port. Otherwise link training will
	 * fail when the power sequencer is freshly used for this port.
	 */
	intel_dp->DP |= DP_PORT_EN;
	if (old_crtc_state->has_audio)
		intel_dp->DP |= DP_AUDIO_OUTPUT_ENABLE;

	I915_WRITE(intel_dp->output_reg, intel_dp->DP);
	POSTING_READ(intel_dp->output_reg);
}