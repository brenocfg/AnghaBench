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
struct dsi_data {scalar_t__ debug_read; scalar_t__ debug_write; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_VC_CTRL (int) ; 
 int /*<<< orphan*/  DSSDBG (char*,int) ; 
 int /*<<< orphan*/  DSSERR (char*) ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct dsi_data*,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ REG_GET (struct dsi_data*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dsi_bus_is_locked (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_read_reg (struct dsi_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_vc_flush_receive_data (struct dsi_data*,int) ; 

__attribute__((used)) static int dsi_vc_send_bta(struct dsi_data *dsi, int channel)
{
	if (dsi->debug_write || dsi->debug_read)
		DSSDBG("dsi_vc_send_bta %d\n", channel);

	WARN_ON(!dsi_bus_is_locked(dsi));

	/* RX_FIFO_NOT_EMPTY */
	if (REG_GET(dsi, DSI_VC_CTRL(channel), 20, 20)) {
		DSSERR("rx fifo not empty when sending BTA, dumping data:\n");
		dsi_vc_flush_receive_data(dsi, channel);
	}

	REG_FLD_MOD(dsi, DSI_VC_CTRL(channel), 1, 6, 6); /* BTA_EN */

	/* flush posted write */
	dsi_read_reg(dsi, DSI_VC_CTRL(channel));

	return 0;
}