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
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {int port; TYPE_1__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {TYPE_2__ base; } ;
struct intel_crtc {int pipe; } ;
struct drm_i915_private {int dummy; } ;
struct drm_connector_state {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum port { ____Placeholder_port } port ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  AUD_CONFIG_LOWER_N_MASK ; 
 int /*<<< orphan*/  AUD_CONFIG_N_PROG_ENABLE ; 
 int /*<<< orphan*/  AUD_CONFIG_N_VALUE_INDEX ; 
 int /*<<< orphan*/  AUD_CONFIG_UPPER_N_MASK ; 
 int /*<<< orphan*/  CPT_AUD_CFG (int) ; 
 int /*<<< orphan*/  CPT_AUD_CNTRL_ST2 ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HAS_PCH_IBX (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBX_AUD_CFG (int) ; 
 int /*<<< orphan*/  IBX_AUD_CNTL_ST2 ; 
 int /*<<< orphan*/  IBX_ELD_VALID (int) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int PORT_A ; 
 int /*<<< orphan*/  VLV_AUD_CFG (int) ; 
 int /*<<< orphan*/  VLV_AUD_CNTL_ST2 ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ intel_crtc_has_dp_encoder (struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  pipe_name (int) ; 
 int /*<<< orphan*/  port_name (int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ilk_audio_codec_disable(struct intel_encoder *encoder,
				    const struct intel_crtc_state *old_crtc_state,
				    const struct drm_connector_state *old_conn_state)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct intel_crtc *crtc = to_intel_crtc(old_crtc_state->base.crtc);
	enum pipe pipe = crtc->pipe;
	enum port port = encoder->port;
	u32 tmp, eldv;
	i915_reg_t aud_config, aud_cntrl_st2;

	DRM_DEBUG_KMS("Disable audio codec on port %c, pipe %c\n",
		      port_name(port), pipe_name(pipe));

	if (WARN_ON(port == PORT_A))
		return;

	if (HAS_PCH_IBX(dev_priv)) {
		aud_config = IBX_AUD_CFG(pipe);
		aud_cntrl_st2 = IBX_AUD_CNTL_ST2;
	} else if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) {
		aud_config = VLV_AUD_CFG(pipe);
		aud_cntrl_st2 = VLV_AUD_CNTL_ST2;
	} else {
		aud_config = CPT_AUD_CFG(pipe);
		aud_cntrl_st2 = CPT_AUD_CNTRL_ST2;
	}

	/* Disable timestamps */
	tmp = I915_READ(aud_config);
	tmp &= ~AUD_CONFIG_N_VALUE_INDEX;
	tmp |= AUD_CONFIG_N_PROG_ENABLE;
	tmp &= ~AUD_CONFIG_UPPER_N_MASK;
	tmp &= ~AUD_CONFIG_LOWER_N_MASK;
	if (intel_crtc_has_dp_encoder(old_crtc_state))
		tmp |= AUD_CONFIG_N_VALUE_INDEX;
	I915_WRITE(aud_config, tmp);

	eldv = IBX_ELD_VALID(port);

	/* Invalidate ELD */
	tmp = I915_READ(aud_cntrl_st2);
	tmp &= ~eldv;
	I915_WRITE(aud_cntrl_st2, tmp);
}