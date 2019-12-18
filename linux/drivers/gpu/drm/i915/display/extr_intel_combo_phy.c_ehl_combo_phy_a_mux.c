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
typedef  int u32 ;
struct TYPE_4__ {TYPE_1__* ddi_port_info; } ;
struct drm_i915_private {TYPE_2__ vbt; } ;
struct TYPE_3__ {int /*<<< orphan*/ * child; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ICL_PHY_MISC_MUX_DDID ; 
 size_t PORT_A ; 
 size_t PORT_D ; 
 int intel_bios_is_dsi_present (struct drm_i915_private*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 ehl_combo_phy_a_mux(struct drm_i915_private *i915, u32 val)
{
	bool ddi_a_present = i915->vbt.ddi_port_info[PORT_A].child != NULL;
	bool ddi_d_present = i915->vbt.ddi_port_info[PORT_D].child != NULL;
	bool dsi_present = intel_bios_is_dsi_present(i915, NULL);

	/*
	 * VBT's 'dvo port' field for child devices references the DDI, not
	 * the PHY.  So if combo PHY A is wired up to drive an external
	 * display, we should see a child device present on PORT_D and
	 * nothing on PORT_A and no DSI.
	 */
	if (ddi_d_present && !ddi_a_present && !dsi_present)
		return val | ICL_PHY_MISC_MUX_DDID;

	/*
	 * If we encounter a VBT that claims to have an external display on
	 * DDI-D _and_ an internal display on DDI-A/DSI leave an error message
	 * in the log and let the internal display win.
	 */
	if (ddi_d_present)
		DRM_ERROR("VBT claims to have both internal and external displays on PHY A.  Configuring for internal.\n");

	return val & ~ICL_PHY_MISC_MUX_DDID;
}