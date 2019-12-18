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
struct drm_i915_private {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  I915_STATE_WARN (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCH_ADPA ; 
 int /*<<< orphan*/  PCH_DP_B ; 
 int /*<<< orphan*/  PCH_DP_C ; 
 int /*<<< orphan*/  PCH_DP_D ; 
 int /*<<< orphan*/  PCH_HDMIB ; 
 int /*<<< orphan*/  PCH_HDMIC ; 
 int /*<<< orphan*/  PCH_HDMID ; 
 int /*<<< orphan*/  PCH_LVDS ; 
 int /*<<< orphan*/  PORT_B ; 
 int /*<<< orphan*/  PORT_C ; 
 int /*<<< orphan*/  PORT_D ; 
 int /*<<< orphan*/  assert_pch_dp_disabled (struct drm_i915_private*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_pch_hdmi_disabled (struct drm_i915_private*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_crt_port_enabled (struct drm_i915_private*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ intel_lvds_port_enabled (struct drm_i915_private*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pipe_name (int) ; 

__attribute__((used)) static void assert_pch_ports_disabled(struct drm_i915_private *dev_priv,
				      enum pipe pipe)
{
	enum pipe port_pipe;

	assert_pch_dp_disabled(dev_priv, pipe, PORT_B, PCH_DP_B);
	assert_pch_dp_disabled(dev_priv, pipe, PORT_C, PCH_DP_C);
	assert_pch_dp_disabled(dev_priv, pipe, PORT_D, PCH_DP_D);

	I915_STATE_WARN(intel_crt_port_enabled(dev_priv, PCH_ADPA, &port_pipe) &&
			port_pipe == pipe,
			"PCH VGA enabled on transcoder %c, should be disabled\n",
			pipe_name(pipe));

	I915_STATE_WARN(intel_lvds_port_enabled(dev_priv, PCH_LVDS, &port_pipe) &&
			port_pipe == pipe,
			"PCH LVDS enabled on transcoder %c, should be disabled\n",
			pipe_name(pipe));

	/* PCH SDVOB multiplex with HDMIB */
	assert_pch_hdmi_disabled(dev_priv, pipe, PORT_B, PCH_HDMIB);
	assert_pch_hdmi_disabled(dev_priv, pipe, PORT_C, PCH_HDMIC);
	assert_pch_hdmi_disabled(dev_priv, pipe, PORT_D, PCH_HDMID);
}