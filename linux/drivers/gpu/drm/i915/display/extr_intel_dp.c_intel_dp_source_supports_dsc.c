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
struct intel_dp {int dummy; } ;
struct intel_crtc_state {scalar_t__ cpu_transcoder; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ TRANSCODER_A ; 
 struct drm_i915_private* dp_to_i915 (struct intel_dp*) ; 

__attribute__((used)) static bool intel_dp_source_supports_dsc(struct intel_dp *intel_dp,
					 const struct intel_crtc_state *pipe_config)
{
	struct drm_i915_private *dev_priv = dp_to_i915(intel_dp);

	return INTEL_GEN(dev_priv) >= 10 &&
		pipe_config->cpu_transcoder != TRANSCODER_A;
}