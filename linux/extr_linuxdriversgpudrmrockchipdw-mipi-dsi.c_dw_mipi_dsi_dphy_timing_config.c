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
struct dw_mipi_dsi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_PHY_TMR_CFG ; 
 int /*<<< orphan*/  DSI_PHY_TMR_LPCLK_CFG ; 
 int MAX_RD_TIME (int) ; 
 int PHY_CLKHS2LP_TIME (int) ; 
 int PHY_CLKLP2HS_TIME (int) ; 
 int PHY_HS2LP_TIME (int) ; 
 int PHY_LP2HS_TIME (int) ; 
 int /*<<< orphan*/  dsi_write (struct dw_mipi_dsi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dw_mipi_dsi_dphy_timing_config(struct dw_mipi_dsi *dsi)
{
	dsi_write(dsi, DSI_PHY_TMR_CFG, PHY_HS2LP_TIME(0x40)
		  | PHY_LP2HS_TIME(0x40) | MAX_RD_TIME(10000));

	dsi_write(dsi, DSI_PHY_TMR_LPCLK_CFG, PHY_CLKHS2LP_TIME(0x40)
		  | PHY_CLKLP2HS_TIME(0x40));
}