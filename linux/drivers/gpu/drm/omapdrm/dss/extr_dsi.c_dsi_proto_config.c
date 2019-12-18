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
typedef  int /*<<< orphan*/  u32 ;
struct dsi_data {scalar_t__ mode; TYPE_1__* data; int /*<<< orphan*/  pix_fmt; } ;
struct TYPE_2__ {int quirks; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DSI_CTRL ; 
 int /*<<< orphan*/  DSI_FIFO_SIZE_32 ; 
 int DSI_QUIRK_DCS_CMD_CONFIG_VC ; 
 int EINVAL ; 
 int /*<<< orphan*/  FLD_MOD (int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ OMAP_DSS_DSI_VIDEO_MODE ; 
 int /*<<< orphan*/  dsi_config_blanking_modes (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_config_cmd_mode_interleaving (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_config_rx_fifo (struct dsi_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_config_tx_fifo (struct dsi_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_config_vp_num_line_buffers (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_config_vp_sync_events (struct dsi_data*) ; 
 int dsi_get_pixel_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_read_reg (struct dsi_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_set_hs_tx_timeout (struct dsi_data*,int,int,int) ; 
 int /*<<< orphan*/  dsi_set_lp_rx_timeout (struct dsi_data*,int,int,int) ; 
 int /*<<< orphan*/  dsi_set_stop_state_counter (struct dsi_data*,int,int,int) ; 
 int /*<<< orphan*/  dsi_set_ta_timeout (struct dsi_data*,int,int,int) ; 
 int /*<<< orphan*/  dsi_vc_initial_config (struct dsi_data*,int) ; 
 int /*<<< orphan*/  dsi_write_reg (struct dsi_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsi_proto_config(struct dsi_data *dsi)
{
	u32 r;
	int buswidth = 0;

	dsi_config_tx_fifo(dsi, DSI_FIFO_SIZE_32,
			DSI_FIFO_SIZE_32,
			DSI_FIFO_SIZE_32,
			DSI_FIFO_SIZE_32);

	dsi_config_rx_fifo(dsi, DSI_FIFO_SIZE_32,
			DSI_FIFO_SIZE_32,
			DSI_FIFO_SIZE_32,
			DSI_FIFO_SIZE_32);

	/* XXX what values for the timeouts? */
	dsi_set_stop_state_counter(dsi, 0x1000, false, false);
	dsi_set_ta_timeout(dsi, 0x1fff, true, true);
	dsi_set_lp_rx_timeout(dsi, 0x1fff, true, true);
	dsi_set_hs_tx_timeout(dsi, 0x1fff, true, true);

	switch (dsi_get_pixel_size(dsi->pix_fmt)) {
	case 16:
		buswidth = 0;
		break;
	case 18:
		buswidth = 1;
		break;
	case 24:
		buswidth = 2;
		break;
	default:
		BUG();
		return -EINVAL;
	}

	r = dsi_read_reg(dsi, DSI_CTRL);
	r = FLD_MOD(r, 1, 1, 1);	/* CS_RX_EN */
	r = FLD_MOD(r, 1, 2, 2);	/* ECC_RX_EN */
	r = FLD_MOD(r, 1, 3, 3);	/* TX_FIFO_ARBITRATION */
	r = FLD_MOD(r, 1, 4, 4);	/* VP_CLK_RATIO, always 1, see errata*/
	r = FLD_MOD(r, buswidth, 7, 6); /* VP_DATA_BUS_WIDTH */
	r = FLD_MOD(r, 0, 8, 8);	/* VP_CLK_POL */
	r = FLD_MOD(r, 1, 14, 14);	/* TRIGGER_RESET_MODE */
	r = FLD_MOD(r, 1, 19, 19);	/* EOT_ENABLE */
	if (!(dsi->data->quirks & DSI_QUIRK_DCS_CMD_CONFIG_VC)) {
		r = FLD_MOD(r, 1, 24, 24);	/* DCS_CMD_ENABLE */
		/* DCS_CMD_CODE, 1=start, 0=continue */
		r = FLD_MOD(r, 0, 25, 25);
	}

	dsi_write_reg(dsi, DSI_CTRL, r);

	dsi_config_vp_num_line_buffers(dsi);

	if (dsi->mode == OMAP_DSS_DSI_VIDEO_MODE) {
		dsi_config_vp_sync_events(dsi);
		dsi_config_blanking_modes(dsi);
		dsi_config_cmd_mode_interleaving(dsi);
	}

	dsi_vc_initial_config(dsi, 0);
	dsi_vc_initial_config(dsi, 1);
	dsi_vc_initial_config(dsi, 2);
	dsi_vc_initial_config(dsi, 3);

	return 0;
}