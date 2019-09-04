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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct intel_crtc_state {int cpu_transcoder; } ;
struct TYPE_2__ {struct drm_device* dev; } ;
struct intel_crtc {int pipe; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
typedef  enum intel_display_power_domain { ____Placeholder_intel_display_power_domain } intel_display_power_domain ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_ULL (int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPECONF (int) ; 
 int PIPECONF_ENABLE ; 
 int PIPE_A ; 
 int PIPE_B ; 
 int PIPE_C ; 
 int POWER_DOMAIN_TRANSCODER (int) ; 
 int TRANSCODER_EDP ; 
#define  TRANS_DDI_EDP_INPUT_A_ON 131 
#define  TRANS_DDI_EDP_INPUT_A_ONOFF 130 
#define  TRANS_DDI_EDP_INPUT_B_ONOFF 129 
#define  TRANS_DDI_EDP_INPUT_C_ONOFF 128 
 int TRANS_DDI_EDP_INPUT_MASK ; 
 int /*<<< orphan*/  TRANS_DDI_FUNC_CTL (int) ; 
 int TRANS_DDI_FUNC_ENABLE ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  intel_display_power_get_if_enabled (struct drm_i915_private*,int) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static bool hsw_get_transcoder_state(struct intel_crtc *crtc,
				     struct intel_crtc_state *pipe_config,
				     u64 *power_domain_mask)
{
	struct drm_device *dev = crtc->base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	enum intel_display_power_domain power_domain;
	u32 tmp;

	/*
	 * The pipe->transcoder mapping is fixed with the exception of the eDP
	 * transcoder handled below.
	 */
	pipe_config->cpu_transcoder = (enum transcoder) crtc->pipe;

	/*
	 * XXX: Do intel_display_power_get_if_enabled before reading this (for
	 * consistency and less surprising code; it's in always on power).
	 */
	tmp = I915_READ(TRANS_DDI_FUNC_CTL(TRANSCODER_EDP));
	if (tmp & TRANS_DDI_FUNC_ENABLE) {
		enum pipe trans_edp_pipe;
		switch (tmp & TRANS_DDI_EDP_INPUT_MASK) {
		default:
			WARN(1, "unknown pipe linked to edp transcoder\n");
			/* fall through */
		case TRANS_DDI_EDP_INPUT_A_ONOFF:
		case TRANS_DDI_EDP_INPUT_A_ON:
			trans_edp_pipe = PIPE_A;
			break;
		case TRANS_DDI_EDP_INPUT_B_ONOFF:
			trans_edp_pipe = PIPE_B;
			break;
		case TRANS_DDI_EDP_INPUT_C_ONOFF:
			trans_edp_pipe = PIPE_C;
			break;
		}

		if (trans_edp_pipe == crtc->pipe)
			pipe_config->cpu_transcoder = TRANSCODER_EDP;
	}

	power_domain = POWER_DOMAIN_TRANSCODER(pipe_config->cpu_transcoder);
	if (!intel_display_power_get_if_enabled(dev_priv, power_domain))
		return false;
	*power_domain_mask |= BIT_ULL(power_domain);

	tmp = I915_READ(PIPECONF(pipe_config->cpu_transcoder));

	return tmp & PIPECONF_ENABLE;
}