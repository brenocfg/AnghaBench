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
struct dsi_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_DSIPHY_CFG10 ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct dsi_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void dsi_cio_disable_lane_override(struct dsi_data *dsi)
{
	/* Disable lane override */
	REG_FLD_MOD(dsi, DSI_DSIPHY_CFG10, 0, 27, 27); /* ENLPTXSCPDAT */
	/* Reset the lane override configuration */
	/* REGLPTXSCPDAT4TO0DXDY */
	REG_FLD_MOD(dsi, DSI_DSIPHY_CFG10, 0, 22, 17);
}