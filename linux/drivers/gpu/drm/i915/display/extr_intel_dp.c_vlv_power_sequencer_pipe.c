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
struct intel_dp {scalar_t__ active_pipe; scalar_t__ pps_pipe; } ;
struct TYPE_2__ {int /*<<< orphan*/  port; } ;
struct intel_digital_port {TYPE_1__ base; } ;
struct drm_i915_private {int /*<<< orphan*/  pps_mutex; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_PIPE ; 
 int PIPE_A ; 
 scalar_t__ WARN_ON (int) ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 struct drm_i915_private* dp_to_i915 (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_init_panel_power_sequencer (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_init_panel_power_sequencer_registers (struct intel_dp*,int) ; 
 int /*<<< orphan*/  intel_dp_is_edp (struct intel_dp*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pipe_name (int) ; 
 int /*<<< orphan*/  port_name (int /*<<< orphan*/ ) ; 
 int vlv_find_free_pps (struct drm_i915_private*) ; 
 int /*<<< orphan*/  vlv_power_sequencer_kick (struct intel_dp*) ; 
 int /*<<< orphan*/  vlv_steal_power_sequencer (struct drm_i915_private*,int) ; 

__attribute__((used)) static enum pipe
vlv_power_sequencer_pipe(struct intel_dp *intel_dp)
{
	struct drm_i915_private *dev_priv = dp_to_i915(intel_dp);
	struct intel_digital_port *intel_dig_port = dp_to_dig_port(intel_dp);
	enum pipe pipe;

	lockdep_assert_held(&dev_priv->pps_mutex);

	/* We should never land here with regular DP ports */
	WARN_ON(!intel_dp_is_edp(intel_dp));

	WARN_ON(intel_dp->active_pipe != INVALID_PIPE &&
		intel_dp->active_pipe != intel_dp->pps_pipe);

	if (intel_dp->pps_pipe != INVALID_PIPE)
		return intel_dp->pps_pipe;

	pipe = vlv_find_free_pps(dev_priv);

	/*
	 * Didn't find one. This should not happen since there
	 * are two power sequencers and up to two eDP ports.
	 */
	if (WARN_ON(pipe == INVALID_PIPE))
		pipe = PIPE_A;

	vlv_steal_power_sequencer(dev_priv, pipe);
	intel_dp->pps_pipe = pipe;

	DRM_DEBUG_KMS("picked pipe %c power sequencer for port %c\n",
		      pipe_name(intel_dp->pps_pipe),
		      port_name(intel_dig_port->base.port));

	/* init power sequencer on this pipe and port */
	intel_dp_init_panel_power_sequencer(intel_dp);
	intel_dp_init_panel_power_sequencer_registers(intel_dp, true);

	/*
	 * Even vdd force doesn't work until we've made
	 * the power sequencer lock in on the port.
	 */
	vlv_power_sequencer_kick(intel_dp);

	return intel_dp->pps_pipe;
}