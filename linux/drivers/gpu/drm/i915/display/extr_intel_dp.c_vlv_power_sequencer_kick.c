#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct intel_dp {int pps_pipe; int /*<<< orphan*/  output_reg; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; } ;
struct intel_digital_port {TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
typedef  enum dpio_phy { ____Placeholder_dpio_phy } dpio_phy ;
typedef  enum dpio_channel { ____Placeholder_dpio_channel } dpio_channel ;
struct TYPE_6__ {int /*<<< orphan*/  dpll; } ;
struct TYPE_5__ {int /*<<< orphan*/  dpll; } ;

/* Variables and functions */
 int DPIO_PHY (int) ; 
 int /*<<< orphan*/  DPLL (int) ; 
 int DPLL_VCO_ENABLE ; 
 int DP_DETECTED ; 
 int DP_LINK_TRAIN_PAT_1 ; 
 int DP_PIPE_SEL (int) ; 
 int DP_PIPE_SEL_CHV (int) ; 
 int DP_PORT_EN ; 
 int DP_PORT_WIDTH (int) ; 
 int DP_PRE_EMPHASIS_0 ; 
 int DP_VOLTAGE_0_4 ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* chv_dpll ; 
 int /*<<< orphan*/  chv_phy_powergate_ch (struct drm_i915_private*,int,int,int) ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 struct drm_i915_private* dp_to_i915 (struct intel_dp*) ; 
 int /*<<< orphan*/  pipe_name (int) ; 
 int /*<<< orphan*/  port_name (int /*<<< orphan*/ ) ; 
 TYPE_2__* vlv_dpll ; 
 int /*<<< orphan*/  vlv_force_pll_off (struct drm_i915_private*,int) ; 
 scalar_t__ vlv_force_pll_on (struct drm_i915_private*,int,int /*<<< orphan*/ *) ; 
 int vlv_pipe_to_channel (int) ; 

__attribute__((used)) static void
vlv_power_sequencer_kick(struct intel_dp *intel_dp)
{
	struct drm_i915_private *dev_priv = dp_to_i915(intel_dp);
	struct intel_digital_port *intel_dig_port = dp_to_dig_port(intel_dp);
	enum pipe pipe = intel_dp->pps_pipe;
	bool pll_enabled, release_cl_override = false;
	enum dpio_phy phy = DPIO_PHY(pipe);
	enum dpio_channel ch = vlv_pipe_to_channel(pipe);
	u32 DP;

	if (WARN(I915_READ(intel_dp->output_reg) & DP_PORT_EN,
		 "skipping pipe %c power sequencer kick due to port %c being active\n",
		 pipe_name(pipe), port_name(intel_dig_port->base.port)))
		return;

	DRM_DEBUG_KMS("kicking pipe %c power sequencer for port %c\n",
		      pipe_name(pipe), port_name(intel_dig_port->base.port));

	/* Preserve the BIOS-computed detected bit. This is
	 * supposed to be read-only.
	 */
	DP = I915_READ(intel_dp->output_reg) & DP_DETECTED;
	DP |= DP_VOLTAGE_0_4 | DP_PRE_EMPHASIS_0;
	DP |= DP_PORT_WIDTH(1);
	DP |= DP_LINK_TRAIN_PAT_1;

	if (IS_CHERRYVIEW(dev_priv))
		DP |= DP_PIPE_SEL_CHV(pipe);
	else
		DP |= DP_PIPE_SEL(pipe);

	pll_enabled = I915_READ(DPLL(pipe)) & DPLL_VCO_ENABLE;

	/*
	 * The DPLL for the pipe must be enabled for this to work.
	 * So enable temporarily it if it's not already enabled.
	 */
	if (!pll_enabled) {
		release_cl_override = IS_CHERRYVIEW(dev_priv) &&
			!chv_phy_powergate_ch(dev_priv, phy, ch, true);

		if (vlv_force_pll_on(dev_priv, pipe, IS_CHERRYVIEW(dev_priv) ?
				     &chv_dpll[0].dpll : &vlv_dpll[0].dpll)) {
			DRM_ERROR("Failed to force on pll for pipe %c!\n",
				  pipe_name(pipe));
			return;
		}
	}

	/*
	 * Similar magic as in intel_dp_enable_port().
	 * We _must_ do this port enable + disable trick
	 * to make this power sequencer lock onto the port.
	 * Otherwise even VDD force bit won't work.
	 */
	I915_WRITE(intel_dp->output_reg, DP);
	POSTING_READ(intel_dp->output_reg);

	I915_WRITE(intel_dp->output_reg, DP | DP_PORT_EN);
	POSTING_READ(intel_dp->output_reg);

	I915_WRITE(intel_dp->output_reg, DP & ~DP_PORT_EN);
	POSTING_READ(intel_dp->output_reg);

	if (!pll_enabled) {
		vlv_force_pll_off(dev_priv, pipe);

		if (release_cl_override)
			chv_phy_powergate_ch(dev_priv, phy, ch, false);
	}
}