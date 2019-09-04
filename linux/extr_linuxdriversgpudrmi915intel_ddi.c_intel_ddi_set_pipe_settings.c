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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {int cpu_transcoder; int pipe_bpp; scalar_t__ limited_color_range; TYPE_1__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int /*<<< orphan*/  TRANS_MSA_10_BPC ; 
 int /*<<< orphan*/  TRANS_MSA_12_BPC ; 
 int /*<<< orphan*/  TRANS_MSA_6_BPC ; 
 int /*<<< orphan*/  TRANS_MSA_8_BPC ; 
 int /*<<< orphan*/  TRANS_MSA_CEA_RANGE ; 
 int /*<<< orphan*/  TRANS_MSA_MISC (int) ; 
 int /*<<< orphan*/  TRANS_MSA_SYNC_CLK ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_crtc_has_dp_encoder (struct intel_crtc_state const*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transcoder_is_dsi (int) ; 

void intel_ddi_set_pipe_settings(const struct intel_crtc_state *crtc_state)
{
	struct intel_crtc *crtc = to_intel_crtc(crtc_state->base.crtc);
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	enum transcoder cpu_transcoder = crtc_state->cpu_transcoder;
	u32 temp;

	if (!intel_crtc_has_dp_encoder(crtc_state))
		return;

	WARN_ON(transcoder_is_dsi(cpu_transcoder));

	temp = TRANS_MSA_SYNC_CLK;

	if (crtc_state->limited_color_range)
		temp |= TRANS_MSA_CEA_RANGE;

	switch (crtc_state->pipe_bpp) {
	case 18:
		temp |= TRANS_MSA_6_BPC;
		break;
	case 24:
		temp |= TRANS_MSA_8_BPC;
		break;
	case 30:
		temp |= TRANS_MSA_10_BPC;
		break;
	case 36:
		temp |= TRANS_MSA_12_BPC;
		break;
	default:
		MISSING_CASE(crtc_state->pipe_bpp);
		break;
	}

	I915_WRITE(TRANS_MSA_MISC(cpu_transcoder), temp);
}