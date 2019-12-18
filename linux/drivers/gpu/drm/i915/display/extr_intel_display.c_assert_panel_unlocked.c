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
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  DP_A ; 
 int HAS_DDI (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_SPLIT (struct drm_i915_private*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_STATE_WARN (int,char*,int /*<<< orphan*/ ) ; 
 int INVALID_PIPE ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  LVDS ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
#define  PANEL_PORT_SELECT_DPA 131 
#define  PANEL_PORT_SELECT_DPC 130 
#define  PANEL_PORT_SELECT_DPD 129 
#define  PANEL_PORT_SELECT_LVDS 128 
 int PANEL_PORT_SELECT_MASK ; 
 int PANEL_POWER_ON ; 
 int PANEL_UNLOCK_MASK ; 
 int PANEL_UNLOCK_REGS ; 
 int /*<<< orphan*/  PCH_DP_C ; 
 int /*<<< orphan*/  PCH_DP_D ; 
 int /*<<< orphan*/  PCH_LVDS ; 
 int /*<<< orphan*/  PORT_A ; 
 int /*<<< orphan*/  PORT_C ; 
 int /*<<< orphan*/  PORT_D ; 
 int /*<<< orphan*/  PP_CONTROL (int) ; 
 int /*<<< orphan*/  PP_ON_DELAYS (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  intel_dp_port_enabled (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  intel_lvds_port_enabled (struct drm_i915_private*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pipe_name (int) ; 

void assert_panel_unlocked(struct drm_i915_private *dev_priv, enum pipe pipe)
{
	i915_reg_t pp_reg;
	u32 val;
	enum pipe panel_pipe = INVALID_PIPE;
	bool locked = true;

	if (WARN_ON(HAS_DDI(dev_priv)))
		return;

	if (HAS_PCH_SPLIT(dev_priv)) {
		u32 port_sel;

		pp_reg = PP_CONTROL(0);
		port_sel = I915_READ(PP_ON_DELAYS(0)) & PANEL_PORT_SELECT_MASK;

		switch (port_sel) {
		case PANEL_PORT_SELECT_LVDS:
			intel_lvds_port_enabled(dev_priv, PCH_LVDS, &panel_pipe);
			break;
		case PANEL_PORT_SELECT_DPA:
			intel_dp_port_enabled(dev_priv, DP_A, PORT_A, &panel_pipe);
			break;
		case PANEL_PORT_SELECT_DPC:
			intel_dp_port_enabled(dev_priv, PCH_DP_C, PORT_C, &panel_pipe);
			break;
		case PANEL_PORT_SELECT_DPD:
			intel_dp_port_enabled(dev_priv, PCH_DP_D, PORT_D, &panel_pipe);
			break;
		default:
			MISSING_CASE(port_sel);
			break;
		}
	} else if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) {
		/* presumably write lock depends on pipe, not port select */
		pp_reg = PP_CONTROL(pipe);
		panel_pipe = pipe;
	} else {
		u32 port_sel;

		pp_reg = PP_CONTROL(0);
		port_sel = I915_READ(PP_ON_DELAYS(0)) & PANEL_PORT_SELECT_MASK;

		WARN_ON(port_sel != PANEL_PORT_SELECT_LVDS);
		intel_lvds_port_enabled(dev_priv, LVDS, &panel_pipe);
	}

	val = I915_READ(pp_reg);
	if (!(val & PANEL_POWER_ON) ||
	    ((val & PANEL_UNLOCK_MASK) == PANEL_UNLOCK_REGS))
		locked = false;

	I915_STATE_WARN(panel_pipe == pipe && locked,
	     "panel assertion failure, pipe %c regs locked\n",
	     pipe_name(pipe));
}