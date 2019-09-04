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
struct intel_dp {int pps_pipe; scalar_t__ active_pipe; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; TYPE_1__ base; } ;
struct intel_digital_port {TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_PIPE ; 
 int PIPE_A ; 
 int PIPE_B ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PP_ON_DELAYS (int) ; 
 scalar_t__ WARN_ON (int) ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 int /*<<< orphan*/  edp_panel_vdd_off_sync (struct intel_dp*) ; 
 int /*<<< orphan*/  pipe_name (int) ; 
 int /*<<< orphan*/  port_name (int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vlv_detach_power_sequencer(struct intel_dp *intel_dp)
{
	struct intel_digital_port *intel_dig_port = dp_to_dig_port(intel_dp);
	struct drm_i915_private *dev_priv = to_i915(intel_dig_port->base.base.dev);
	enum pipe pipe = intel_dp->pps_pipe;
	i915_reg_t pp_on_reg = PP_ON_DELAYS(pipe);

	WARN_ON(intel_dp->active_pipe != INVALID_PIPE);

	if (WARN_ON(pipe != PIPE_A && pipe != PIPE_B))
		return;

	edp_panel_vdd_off_sync(intel_dp);

	/*
	 * VLV seems to get confused when multiple power sequencers
	 * have the same port selected (even if only one has power/vdd
	 * enabled). The failure manifests as vlv_wait_port_ready() failing
	 * CHV on the other hand doesn't seem to mind having the same port
	 * selected in multiple power sequencers, but let's clear the
	 * port select always when logically disconnecting a power sequencer
	 * from a port.
	 */
	DRM_DEBUG_KMS("detaching pipe %c power sequencer from port %c\n",
		      pipe_name(pipe), port_name(intel_dig_port->base.port));
	I915_WRITE(pp_on_reg, 0);
	POSTING_READ(pp_on_reg);

	intel_dp->pps_pipe = INVALID_PIPE;
}