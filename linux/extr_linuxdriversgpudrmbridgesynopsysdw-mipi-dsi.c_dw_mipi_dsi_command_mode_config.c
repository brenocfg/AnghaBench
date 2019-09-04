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
 int /*<<< orphan*/  DSI_BTA_TO_CNT ; 
 int /*<<< orphan*/  DSI_MODE_CFG ; 
 int /*<<< orphan*/  DSI_TO_CNT_CFG ; 
 int ENABLE_CMD_MODE ; 
 int HSTX_TO_CNT (int) ; 
 int LPRX_TO_CNT (int) ; 
 int /*<<< orphan*/  dsi_write (struct dw_mipi_dsi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dw_mipi_dsi_command_mode_config(struct dw_mipi_dsi *dsi)
{
	/*
	 * TODO dw drv improvements
	 * compute high speed transmission counter timeout according
	 * to the timeout clock division (TO_CLK_DIVISION) and byte lane...
	 */
	dsi_write(dsi, DSI_TO_CNT_CFG, HSTX_TO_CNT(1000) | LPRX_TO_CNT(1000));
	/*
	 * TODO dw drv improvements
	 * the Bus-Turn-Around Timeout Counter should be computed
	 * according to byte lane...
	 */
	dsi_write(dsi, DSI_BTA_TO_CNT, 0xd00);
	dsi_write(dsi, DSI_MODE_CFG, ENABLE_CMD_MODE);
}