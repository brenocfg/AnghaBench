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
struct intel_dp {scalar_t__ pps_pipe; } ;
struct TYPE_2__ {int port; } ;
struct intel_digital_port {TYPE_1__ base; } ;
struct drm_i915_private {int /*<<< orphan*/  pps_mutex; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ INVALID_PIPE ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 struct drm_i915_private* dp_to_i915 (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_init_panel_power_sequencer (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_init_panel_power_sequencer_registers (struct intel_dp*,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pipe_name (scalar_t__) ; 
 int /*<<< orphan*/  port_name (int) ; 
 void* vlv_initial_pps_pipe (struct drm_i915_private*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlv_pipe_any ; 
 int /*<<< orphan*/  vlv_pipe_has_pp_on ; 
 int /*<<< orphan*/  vlv_pipe_has_vdd_on ; 

__attribute__((used)) static void
vlv_initial_power_sequencer_setup(struct intel_dp *intel_dp)
{
	struct drm_i915_private *dev_priv = dp_to_i915(intel_dp);
	struct intel_digital_port *intel_dig_port = dp_to_dig_port(intel_dp);
	enum port port = intel_dig_port->base.port;

	lockdep_assert_held(&dev_priv->pps_mutex);

	/* try to find a pipe with this port selected */
	/* first pick one where the panel is on */
	intel_dp->pps_pipe = vlv_initial_pps_pipe(dev_priv, port,
						  vlv_pipe_has_pp_on);
	/* didn't find one? pick one where vdd is on */
	if (intel_dp->pps_pipe == INVALID_PIPE)
		intel_dp->pps_pipe = vlv_initial_pps_pipe(dev_priv, port,
							  vlv_pipe_has_vdd_on);
	/* didn't find one? pick one with just the correct port */
	if (intel_dp->pps_pipe == INVALID_PIPE)
		intel_dp->pps_pipe = vlv_initial_pps_pipe(dev_priv, port,
							  vlv_pipe_any);

	/* didn't find one? just let vlv_power_sequencer_pipe() pick one when needed */
	if (intel_dp->pps_pipe == INVALID_PIPE) {
		DRM_DEBUG_KMS("no initial power sequencer for port %c\n",
			      port_name(port));
		return;
	}

	DRM_DEBUG_KMS("initial power sequencer for port %c: pipe %c\n",
		      port_name(port), pipe_name(intel_dp->pps_pipe));

	intel_dp_init_panel_power_sequencer(intel_dp);
	intel_dp_init_panel_power_sequencer_registers(intel_dp, false);
}