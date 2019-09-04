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
 int /*<<< orphan*/  DSI_CLK_CTRL ; 
 int /*<<< orphan*/  DSI_COMPLEXIO_POWER_OFF ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct dsi_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dsi_cio_power (struct dsi_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_disable_pads (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_disable_scp_clk (struct dsi_data*) ; 

__attribute__((used)) static void dsi_cio_uninit(struct dsi_data *dsi)
{
	/* DDR_CLK_ALWAYS_ON */
	REG_FLD_MOD(dsi, DSI_CLK_CTRL, 0, 13, 13);

	dsi_cio_power(dsi, DSI_COMPLEXIO_POWER_OFF);
	dsi_disable_scp_clk(dsi);
	dsi_disable_pads(dsi);
}