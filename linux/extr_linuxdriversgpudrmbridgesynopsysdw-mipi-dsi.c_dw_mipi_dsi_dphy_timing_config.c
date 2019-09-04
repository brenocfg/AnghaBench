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
struct dw_mipi_dsi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_PHY_TMR_CFG ; 
 int /*<<< orphan*/  DSI_PHY_TMR_LPCLK_CFG ; 
 int /*<<< orphan*/  DSI_PHY_TMR_RD_CFG ; 
 int /*<<< orphan*/  DSI_VERSION ; 
 int HWVER_131 ; 
 int MAX_RD_TIME (int) ; 
 int MAX_RD_TIME_V131 (int) ; 
 int PHY_CLKHS2LP_TIME (int) ; 
 int PHY_CLKLP2HS_TIME (int) ; 
 int PHY_HS2LP_TIME (int) ; 
 int PHY_HS2LP_TIME_V131 (int) ; 
 int PHY_LP2HS_TIME (int) ; 
 int PHY_LP2HS_TIME_V131 (int) ; 
 int VERSION ; 
 int dsi_read (struct dw_mipi_dsi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_write (struct dw_mipi_dsi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dw_mipi_dsi_dphy_timing_config(struct dw_mipi_dsi *dsi)
{
	u32 hw_version;

	/*
	 * TODO dw drv improvements
	 * data & clock lane timers should be computed according to panel
	 * blankings and to the automatic clock lane control mode...
	 * note: DSI_PHY_TMR_CFG.MAX_RD_TIME should be in line with
	 * DSI_CMD_MODE_CFG.MAX_RD_PKT_SIZE_LP (see CMD_MODE_ALL_LP)
	 */

	hw_version = dsi_read(dsi, DSI_VERSION) & VERSION;

	if (hw_version >= HWVER_131) {
		dsi_write(dsi, DSI_PHY_TMR_CFG, PHY_HS2LP_TIME_V131(0x40) |
			  PHY_LP2HS_TIME_V131(0x40));
		dsi_write(dsi, DSI_PHY_TMR_RD_CFG, MAX_RD_TIME_V131(10000));
	} else {
		dsi_write(dsi, DSI_PHY_TMR_CFG, PHY_HS2LP_TIME(0x40) |
			  PHY_LP2HS_TIME(0x40) | MAX_RD_TIME(10000));
	}

	dsi_write(dsi, DSI_PHY_TMR_LPCLK_CFG, PHY_CLKHS2LP_TIME(0x40)
		  | PHY_CLKLP2HS_TIME(0x40));
}