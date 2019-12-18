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
struct intel_dp {int /*<<< orphan*/  dsc_dpcd; } ;
struct intel_crtc_state {int /*<<< orphan*/  fec_enable; } ;

/* Variables and functions */
 scalar_t__ drm_dp_sink_supports_dsc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dp_is_edp (struct intel_dp*) ; 
 scalar_t__ intel_dp_source_supports_dsc (struct intel_dp*,struct intel_crtc_state const*) ; 

__attribute__((used)) static bool intel_dp_supports_dsc(struct intel_dp *intel_dp,
				  const struct intel_crtc_state *pipe_config)
{
	if (!intel_dp_is_edp(intel_dp) && !pipe_config->fec_enable)
		return false;

	return intel_dp_source_supports_dsc(intel_dp, pipe_config) &&
		drm_dp_sink_supports_dsc(intel_dp->dsc_dpcd);
}