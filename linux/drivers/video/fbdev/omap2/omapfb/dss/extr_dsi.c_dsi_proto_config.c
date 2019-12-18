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
typedef  int /*<<< orphan*/  u32 ;
struct platform_device {int dummy; } ;
struct dsi_data {scalar_t__ mode; int /*<<< orphan*/  pix_fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DSI_CTRL ; 
 int /*<<< orphan*/  DSI_FIFO_SIZE_32 ; 
 int EINVAL ; 
 int /*<<< orphan*/  FEAT_DSI_DCS_CMD_CONFIG_VC ; 
 int /*<<< orphan*/  FLD_MOD (int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ OMAP_DSS_DSI_VIDEO_MODE ; 
 int /*<<< orphan*/  dsi_config_blanking_modes (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_config_cmd_mode_interleaving (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_config_rx_fifo (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_config_tx_fifo (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_config_vp_num_line_buffers (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_config_vp_sync_events (struct platform_device*) ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 
 int dsi_get_pixel_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_read_reg (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_set_hs_tx_timeout (struct platform_device*,int,int,int) ; 
 int /*<<< orphan*/  dsi_set_lp_rx_timeout (struct platform_device*,int,int,int) ; 
 int /*<<< orphan*/  dsi_set_stop_state_counter (struct platform_device*,int,int,int) ; 
 int /*<<< orphan*/  dsi_set_ta_timeout (struct platform_device*,int,int,int) ; 
 int /*<<< orphan*/  dsi_vc_initial_config (struct platform_device*,int) ; 
 int /*<<< orphan*/  dsi_write_reg (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dss_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsi_proto_config(struct platform_device *dsidev)
{
	struct dsi_data *dsi = dsi_get_dsidrv_data(dsidev);
	u32 r;
	int buswidth = 0;

	dsi_config_tx_fifo(dsidev, DSI_FIFO_SIZE_32,
			DSI_FIFO_SIZE_32,
			DSI_FIFO_SIZE_32,
			DSI_FIFO_SIZE_32);

	dsi_config_rx_fifo(dsidev, DSI_FIFO_SIZE_32,
			DSI_FIFO_SIZE_32,
			DSI_FIFO_SIZE_32,
			DSI_FIFO_SIZE_32);

	/* XXX what values for the timeouts? */
	dsi_set_stop_state_counter(dsidev, 0x1000, false, false);
	dsi_set_ta_timeout(dsidev, 0x1fff, true, true);
	dsi_set_lp_rx_timeout(dsidev, 0x1fff, true, true);
	dsi_set_hs_tx_timeout(dsidev, 0x1fff, true, true);

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

	r = dsi_read_reg(dsidev, DSI_CTRL);
	r = FLD_MOD(r, 1, 1, 1);	/* CS_RX_EN */
	r = FLD_MOD(r, 1, 2, 2);	/* ECC_RX_EN */
	r = FLD_MOD(r, 1, 3, 3);	/* TX_FIFO_ARBITRATION */
	r = FLD_MOD(r, 1, 4, 4);	/* VP_CLK_RATIO, always 1, see errata*/
	r = FLD_MOD(r, buswidth, 7, 6); /* VP_DATA_BUS_WIDTH */
	r = FLD_MOD(r, 0, 8, 8);	/* VP_CLK_POL */
	r = FLD_MOD(r, 1, 14, 14);	/* TRIGGER_RESET_MODE */
	r = FLD_MOD(r, 1, 19, 19);	/* EOT_ENABLE */
	if (!dss_has_feature(FEAT_DSI_DCS_CMD_CONFIG_VC)) {
		r = FLD_MOD(r, 1, 24, 24);	/* DCS_CMD_ENABLE */
		/* DCS_CMD_CODE, 1=start, 0=continue */
		r = FLD_MOD(r, 0, 25, 25);
	}

	dsi_write_reg(dsidev, DSI_CTRL, r);

	dsi_config_vp_num_line_buffers(dsidev);

	if (dsi->mode == OMAP_DSS_DSI_VIDEO_MODE) {
		dsi_config_vp_sync_events(dsidev);
		dsi_config_blanking_modes(dsidev);
		dsi_config_cmd_mode_interleaving(dsidev);
	}

	dsi_vc_initial_config(dsidev, 0);
	dsi_vc_initial_config(dsidev, 1);
	dsi_vc_initial_config(dsidev, 2);
	dsi_vc_initial_config(dsidev, 3);

	return 0;
}