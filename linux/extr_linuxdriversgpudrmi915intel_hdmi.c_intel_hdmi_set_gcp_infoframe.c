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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  adjusted_mode; int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {TYPE_1__ base; int /*<<< orphan*/  pipe_bpp; int /*<<< orphan*/  cpu_transcoder; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; } ;
struct drm_i915_private {int dummy; } ;
struct drm_encoder {int /*<<< orphan*/  dev; } ;
struct drm_connector_state {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  GCP_COLOR_INDICATION ; 
 int /*<<< orphan*/  GCP_DEFAULT_PHASE_ENABLE ; 
 scalar_t__ HAS_DDI (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_SPLIT (struct drm_i915_private*) ; 
 int /*<<< orphan*/  HSW_TVIDEO_DIP_GCP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  TVIDEO_DIP_GCP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLV_TVIDEO_DIP_GCP (int /*<<< orphan*/ ) ; 
 scalar_t__ gcp_default_phase_possible (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ hdmi_sink_is_deep_color (struct drm_connector_state const*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool intel_hdmi_set_gcp_infoframe(struct drm_encoder *encoder,
					 const struct intel_crtc_state *crtc_state,
					 const struct drm_connector_state *conn_state)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->dev);
	struct intel_crtc *crtc = to_intel_crtc(crtc_state->base.crtc);
	i915_reg_t reg;
	u32 val = 0;

	if (HAS_DDI(dev_priv))
		reg = HSW_TVIDEO_DIP_GCP(crtc_state->cpu_transcoder);
	else if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		reg = VLV_TVIDEO_DIP_GCP(crtc->pipe);
	else if (HAS_PCH_SPLIT(dev_priv))
		reg = TVIDEO_DIP_GCP(crtc->pipe);
	else
		return false;

	/* Indicate color depth whenever the sink supports deep color */
	if (hdmi_sink_is_deep_color(conn_state))
		val |= GCP_COLOR_INDICATION;

	/* Enable default_phase whenever the display mode is suitably aligned */
	if (gcp_default_phase_possible(crtc_state->pipe_bpp,
				       &crtc_state->base.adjusted_mode))
		val |= GCP_DEFAULT_PHASE_ENABLE;

	I915_WRITE(reg, val);

	return val != 0;
}