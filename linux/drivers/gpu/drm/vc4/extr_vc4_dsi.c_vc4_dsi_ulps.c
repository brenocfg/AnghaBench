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
typedef  int u32 ;
struct vc4_dsi {int mode_flags; int lanes; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DSI1_STAT_PHY_CLOCK_STOP ; 
 int DSI1_STAT_PHY_CLOCK_ULPS ; 
 int DSI1_STAT_PHY_D0_STOP ; 
 int DSI1_STAT_PHY_D0_ULPS ; 
 int DSI1_STAT_PHY_D1_STOP ; 
 int DSI1_STAT_PHY_D1_ULPS ; 
 int DSI1_STAT_PHY_D2_STOP ; 
 int DSI1_STAT_PHY_D2_ULPS ; 
 int DSI1_STAT_PHY_D3_STOP ; 
 int DSI1_STAT_PHY_D3_ULPS ; 
 int DSI_PHYC_DLANE0_ULPS ; 
 int DSI_PHYC_DLANE1_ULPS ; 
 int DSI_PHYC_DLANE2_ULPS ; 
 int DSI_PHYC_DLANE3_ULPS ; 
 int DSI_PORT_BIT (int /*<<< orphan*/ ) ; 
 int DSI_PORT_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSI_PORT_WRITE (int /*<<< orphan*/ ,int) ; 
 int MIPI_DSI_CLOCK_NON_CONTINUOUS ; 
 int /*<<< orphan*/  PHYC ; 
 int /*<<< orphan*/  PHYC_CLANE_ULPS ; 
 int /*<<< orphan*/  PHY_AFEC0 ; 
 int /*<<< orphan*/  PHY_AFEC0_LATCH_ULPS ; 
 int /*<<< orphan*/  STAT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  vc4_dsi_latch_ulps (struct vc4_dsi*,int) ; 
 int wait_for (int,int) ; 

__attribute__((used)) static void vc4_dsi_ulps(struct vc4_dsi *dsi, bool ulps)
{
	bool non_continuous = dsi->mode_flags & MIPI_DSI_CLOCK_NON_CONTINUOUS;
	u32 phyc_ulps = ((non_continuous ? DSI_PORT_BIT(PHYC_CLANE_ULPS) : 0) |
			 DSI_PHYC_DLANE0_ULPS |
			 (dsi->lanes > 1 ? DSI_PHYC_DLANE1_ULPS : 0) |
			 (dsi->lanes > 2 ? DSI_PHYC_DLANE2_ULPS : 0) |
			 (dsi->lanes > 3 ? DSI_PHYC_DLANE3_ULPS : 0));
	u32 stat_ulps = ((non_continuous ? DSI1_STAT_PHY_CLOCK_ULPS : 0) |
			 DSI1_STAT_PHY_D0_ULPS |
			 (dsi->lanes > 1 ? DSI1_STAT_PHY_D1_ULPS : 0) |
			 (dsi->lanes > 2 ? DSI1_STAT_PHY_D2_ULPS : 0) |
			 (dsi->lanes > 3 ? DSI1_STAT_PHY_D3_ULPS : 0));
	u32 stat_stop = ((non_continuous ? DSI1_STAT_PHY_CLOCK_STOP : 0) |
			 DSI1_STAT_PHY_D0_STOP |
			 (dsi->lanes > 1 ? DSI1_STAT_PHY_D1_STOP : 0) |
			 (dsi->lanes > 2 ? DSI1_STAT_PHY_D2_STOP : 0) |
			 (dsi->lanes > 3 ? DSI1_STAT_PHY_D3_STOP : 0));
	int ret;
	bool ulps_currently_enabled = (DSI_PORT_READ(PHY_AFEC0) &
				       DSI_PORT_BIT(PHY_AFEC0_LATCH_ULPS));

	if (ulps == ulps_currently_enabled)
		return;

	DSI_PORT_WRITE(STAT, stat_ulps);
	DSI_PORT_WRITE(PHYC, DSI_PORT_READ(PHYC) | phyc_ulps);
	ret = wait_for((DSI_PORT_READ(STAT) & stat_ulps) == stat_ulps, 200);
	if (ret) {
		dev_warn(&dsi->pdev->dev,
			 "Timeout waiting for DSI ULPS entry: STAT 0x%08x",
			 DSI_PORT_READ(STAT));
		DSI_PORT_WRITE(PHYC, DSI_PORT_READ(PHYC) & ~phyc_ulps);
		vc4_dsi_latch_ulps(dsi, false);
		return;
	}

	/* The DSI module can't be disabled while the module is
	 * generating ULPS state.  So, to be able to disable the
	 * module, we have the AFE latch the ULPS state and continue
	 * on to having the module enter STOP.
	 */
	vc4_dsi_latch_ulps(dsi, ulps);

	DSI_PORT_WRITE(STAT, stat_stop);
	DSI_PORT_WRITE(PHYC, DSI_PORT_READ(PHYC) & ~phyc_ulps);
	ret = wait_for((DSI_PORT_READ(STAT) & stat_stop) == stat_stop, 200);
	if (ret) {
		dev_warn(&dsi->pdev->dev,
			 "Timeout waiting for DSI STOP entry: STAT 0x%08x",
			 DSI_PORT_READ(STAT));
		DSI_PORT_WRITE(PHYC, DSI_PORT_READ(PHYC) & ~phyc_ulps);
		return;
	}
}