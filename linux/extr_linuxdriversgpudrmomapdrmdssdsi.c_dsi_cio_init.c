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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int ddr_clk_always_on; } ;
struct dsi_data {int ulps_enabled; int num_lanes_supported; scalar_t__ mode; TYPE_2__ vm_timings; TYPE_1__* lanes; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_3__ {scalar_t__ function; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_CLK_CTRL ; 
 int /*<<< orphan*/  DSI_COMPLEXIO_CFG1 ; 
 int /*<<< orphan*/  DSI_COMPLEXIO_POWER_OFF ; 
 int /*<<< orphan*/  DSI_COMPLEXIO_POWER_ON ; 
 int /*<<< orphan*/  DSI_DSIPHY_CFG5 ; 
 scalar_t__ DSI_LANE_UNUSED ; 
 int /*<<< orphan*/  DSI_TIMING1 ; 
 int /*<<< orphan*/  DSSDBG (char*) ; 
 int /*<<< orphan*/  DSSERR (char*) ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  FLD_MOD (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 scalar_t__ OMAP_DSS_DSI_VIDEO_MODE ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct dsi_data*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  dsi_cio_disable_lane_override (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_cio_enable_lane_override (struct dsi_data*,unsigned int,int /*<<< orphan*/ ) ; 
 int dsi_cio_power (struct dsi_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_cio_timings (struct dsi_data*) ; 
 int dsi_cio_wait_tx_clk_esc_reset (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_disable_pads (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_disable_scp_clk (struct dsi_data*) ; 
 int dsi_enable_pads (struct dsi_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_enable_scp_clk (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_get_lane_mask (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_if_enable (struct dsi_data*,int) ; 
 int /*<<< orphan*/  dsi_read_reg (struct dsi_data*,int /*<<< orphan*/ ) ; 
 int dsi_set_lane_config (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_write_reg (struct dsi_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_to_ktime (int) ; 
 int /*<<< orphan*/  schedule_hrtimeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_bit_change (struct dsi_data*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int dsi_cio_init(struct dsi_data *dsi)
{
	int r;
	u32 l;

	DSSDBG("DSI CIO init starts");

	r = dsi_enable_pads(dsi, dsi_get_lane_mask(dsi));
	if (r)
		return r;

	dsi_enable_scp_clk(dsi);

	/* A dummy read using the SCP interface to any DSIPHY register is
	 * required after DSIPHY reset to complete the reset of the DSI complex
	 * I/O. */
	dsi_read_reg(dsi, DSI_DSIPHY_CFG5);

	if (!wait_for_bit_change(dsi, DSI_DSIPHY_CFG5, 30, 1)) {
		DSSERR("CIO SCP Clock domain not coming out of reset.\n");
		r = -EIO;
		goto err_scp_clk_dom;
	}

	r = dsi_set_lane_config(dsi);
	if (r)
		goto err_scp_clk_dom;

	/* set TX STOP MODE timer to maximum for this operation */
	l = dsi_read_reg(dsi, DSI_TIMING1);
	l = FLD_MOD(l, 1, 15, 15);	/* FORCE_TX_STOP_MODE_IO */
	l = FLD_MOD(l, 1, 14, 14);	/* STOP_STATE_X16_IO */
	l = FLD_MOD(l, 1, 13, 13);	/* STOP_STATE_X4_IO */
	l = FLD_MOD(l, 0x1fff, 12, 0);	/* STOP_STATE_COUNTER_IO */
	dsi_write_reg(dsi, DSI_TIMING1, l);

	if (dsi->ulps_enabled) {
		unsigned int mask_p;
		int i;

		DSSDBG("manual ulps exit\n");

		/* ULPS is exited by Mark-1 state for 1ms, followed by
		 * stop state. DSS HW cannot do this via the normal
		 * ULPS exit sequence, as after reset the DSS HW thinks
		 * that we are not in ULPS mode, and refuses to send the
		 * sequence. So we need to send the ULPS exit sequence
		 * manually by setting positive lines high and negative lines
		 * low for 1ms.
		 */

		mask_p = 0;

		for (i = 0; i < dsi->num_lanes_supported; ++i) {
			if (dsi->lanes[i].function == DSI_LANE_UNUSED)
				continue;
			mask_p |= 1 << i;
		}

		dsi_cio_enable_lane_override(dsi, mask_p, 0);
	}

	r = dsi_cio_power(dsi, DSI_COMPLEXIO_POWER_ON);
	if (r)
		goto err_cio_pwr;

	if (!wait_for_bit_change(dsi, DSI_COMPLEXIO_CFG1, 29, 1)) {
		DSSERR("CIO PWR clock domain not coming out of reset.\n");
		r = -ENODEV;
		goto err_cio_pwr_dom;
	}

	dsi_if_enable(dsi, true);
	dsi_if_enable(dsi, false);
	REG_FLD_MOD(dsi, DSI_CLK_CTRL, 1, 20, 20); /* LP_CLK_ENABLE */

	r = dsi_cio_wait_tx_clk_esc_reset(dsi);
	if (r)
		goto err_tx_clk_esc_rst;

	if (dsi->ulps_enabled) {
		/* Keep Mark-1 state for 1ms (as per DSI spec) */
		ktime_t wait = ns_to_ktime(1000 * 1000);
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_hrtimeout(&wait, HRTIMER_MODE_REL);

		/* Disable the override. The lanes should be set to Mark-11
		 * state by the HW */
		dsi_cio_disable_lane_override(dsi);
	}

	/* FORCE_TX_STOP_MODE_IO */
	REG_FLD_MOD(dsi, DSI_TIMING1, 0, 15, 15);

	dsi_cio_timings(dsi);

	if (dsi->mode == OMAP_DSS_DSI_VIDEO_MODE) {
		/* DDR_CLK_ALWAYS_ON */
		REG_FLD_MOD(dsi, DSI_CLK_CTRL,
			dsi->vm_timings.ddr_clk_always_on, 13, 13);
	}

	dsi->ulps_enabled = false;

	DSSDBG("CIO init done\n");

	return 0;

err_tx_clk_esc_rst:
	REG_FLD_MOD(dsi, DSI_CLK_CTRL, 0, 20, 20); /* LP_CLK_ENABLE */
err_cio_pwr_dom:
	dsi_cio_power(dsi, DSI_COMPLEXIO_POWER_OFF);
err_cio_pwr:
	if (dsi->ulps_enabled)
		dsi_cio_disable_lane_override(dsi);
err_scp_clk_dom:
	dsi_disable_scp_clk(dsi);
	dsi_disable_pads(dsi);
	return r;
}