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
struct dsi_data {int ulps_enabled; int num_lanes_supported; TYPE_1__* lanes; } ;
struct TYPE_2__ {scalar_t__ function; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSI_CIO_IRQ_ULPSACTIVENOT_ALL0 ; 
 int /*<<< orphan*/  DSI_CLK_CTRL ; 
 int /*<<< orphan*/  DSI_COMPLEXIO_CFG2 ; 
 int /*<<< orphan*/  DSI_COMPLEXIO_POWER_ULPS ; 
 scalar_t__ DSI_LANE_UNUSED ; 
 int /*<<< orphan*/  DSSDBG (char*) ; 
 int /*<<< orphan*/  DSSERR (char*) ; 
 int EIO ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct dsi_data*,int /*<<< orphan*/ ,unsigned int,int,int) ; 
 scalar_t__ REG_GET (struct dsi_data*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  completion ; 
 int /*<<< orphan*/  dsi_bus_is_locked (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_cio_power (struct dsi_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_completion_handler ; 
 int /*<<< orphan*/  dsi_force_tx_stop_mode_io (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_if_enable (struct dsi_data*,int) ; 
 int /*<<< orphan*/  dsi_read_reg (struct dsi_data*,int /*<<< orphan*/ ) ; 
 int dsi_register_isr_cio (struct dsi_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_sync_vc (struct dsi_data*,int) ; 
 int /*<<< orphan*/  dsi_unregister_isr_cio (struct dsi_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_vc_enable (struct dsi_data*,int,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 scalar_t__ wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsi_enter_ulps(struct dsi_data *dsi)
{
	DECLARE_COMPLETION_ONSTACK(completion);
	int r, i;
	unsigned int mask;

	DSSDBG("Entering ULPS");

	WARN_ON(!dsi_bus_is_locked(dsi));

	WARN_ON(dsi->ulps_enabled);

	if (dsi->ulps_enabled)
		return 0;

	/* DDR_CLK_ALWAYS_ON */
	if (REG_GET(dsi, DSI_CLK_CTRL, 13, 13)) {
		dsi_if_enable(dsi, 0);
		REG_FLD_MOD(dsi, DSI_CLK_CTRL, 0, 13, 13);
		dsi_if_enable(dsi, 1);
	}

	dsi_sync_vc(dsi, 0);
	dsi_sync_vc(dsi, 1);
	dsi_sync_vc(dsi, 2);
	dsi_sync_vc(dsi, 3);

	dsi_force_tx_stop_mode_io(dsi);

	dsi_vc_enable(dsi, 0, false);
	dsi_vc_enable(dsi, 1, false);
	dsi_vc_enable(dsi, 2, false);
	dsi_vc_enable(dsi, 3, false);

	if (REG_GET(dsi, DSI_COMPLEXIO_CFG2, 16, 16)) {	/* HS_BUSY */
		DSSERR("HS busy when enabling ULPS\n");
		return -EIO;
	}

	if (REG_GET(dsi, DSI_COMPLEXIO_CFG2, 17, 17)) {	/* LP_BUSY */
		DSSERR("LP busy when enabling ULPS\n");
		return -EIO;
	}

	r = dsi_register_isr_cio(dsi, dsi_completion_handler, &completion,
			DSI_CIO_IRQ_ULPSACTIVENOT_ALL0);
	if (r)
		return r;

	mask = 0;

	for (i = 0; i < dsi->num_lanes_supported; ++i) {
		if (dsi->lanes[i].function == DSI_LANE_UNUSED)
			continue;
		mask |= 1 << i;
	}
	/* Assert TxRequestEsc for data lanes and TxUlpsClk for clk lane */
	/* LANEx_ULPS_SIG2 */
	REG_FLD_MOD(dsi, DSI_COMPLEXIO_CFG2, mask, 9, 5);

	/* flush posted write and wait for SCP interface to finish the write */
	dsi_read_reg(dsi, DSI_COMPLEXIO_CFG2);

	if (wait_for_completion_timeout(&completion,
				msecs_to_jiffies(1000)) == 0) {
		DSSERR("ULPS enable timeout\n");
		r = -EIO;
		goto err;
	}

	dsi_unregister_isr_cio(dsi, dsi_completion_handler, &completion,
			DSI_CIO_IRQ_ULPSACTIVENOT_ALL0);

	/* Reset LANEx_ULPS_SIG2 */
	REG_FLD_MOD(dsi, DSI_COMPLEXIO_CFG2, 0, 9, 5);

	/* flush posted write and wait for SCP interface to finish the write */
	dsi_read_reg(dsi, DSI_COMPLEXIO_CFG2);

	dsi_cio_power(dsi, DSI_COMPLEXIO_POWER_ULPS);

	dsi_if_enable(dsi, false);

	dsi->ulps_enabled = true;

	return 0;

err:
	dsi_unregister_isr_cio(dsi, dsi_completion_handler, &completion,
			DSI_CIO_IRQ_ULPSACTIVENOT_ALL0);
	return r;
}