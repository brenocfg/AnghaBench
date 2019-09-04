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
struct dw_mipi_dsi {int /*<<< orphan*/  lanes; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_PHY_IF_CFG ; 
 int N_LANES (int /*<<< orphan*/ ) ; 
 int PHY_STOP_WAIT_TIME (int) ; 
 int /*<<< orphan*/  dsi_write (struct dw_mipi_dsi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dw_mipi_dsi_dphy_interface_config(struct dw_mipi_dsi *dsi)
{
	/*
	 * TODO dw drv improvements
	 * stop wait time should be the maximum between host dsi
	 * and panel stop wait times
	 */
	dsi_write(dsi, DSI_PHY_IF_CFG, PHY_STOP_WAIT_TIME(0x20) |
		  N_LANES(dsi->lanes));
}