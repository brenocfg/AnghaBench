#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int dispc_channel; } ;
struct TYPE_9__ {int stallmode; int fifohandcheck; scalar_t__ lcden_sig_polarity; int /*<<< orphan*/  video_port_width; int /*<<< orphan*/  io_pad_mode; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;
struct dsi_data {scalar_t__ module_id; scalar_t__ mode; int /*<<< orphan*/  dss; TYPE_1__ output; TYPE_5__ mgr_config; int /*<<< orphan*/  pix_fmt; TYPE_3__ vm; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY_FLAGS_DE_HIGH ; 
 int /*<<< orphan*/  DISPLAY_FLAGS_DE_LOW ; 
 int /*<<< orphan*/  DISPLAY_FLAGS_HSYNC_HIGH ; 
 int /*<<< orphan*/  DISPLAY_FLAGS_HSYNC_LOW ; 
 int /*<<< orphan*/  DISPLAY_FLAGS_INTERLACED ; 
 int /*<<< orphan*/  DISPLAY_FLAGS_PIXDATA_NEGEDGE ; 
 int /*<<< orphan*/  DISPLAY_FLAGS_PIXDATA_POSEDGE ; 
 int /*<<< orphan*/  DISPLAY_FLAGS_SYNC_NEGEDGE ; 
 int /*<<< orphan*/  DISPLAY_FLAGS_SYNC_POSEDGE ; 
 int /*<<< orphan*/  DISPLAY_FLAGS_VSYNC_HIGH ; 
 int /*<<< orphan*/  DISPLAY_FLAGS_VSYNC_LOW ; 
 int /*<<< orphan*/  DSSERR (char*) ; 
 int /*<<< orphan*/  DSS_CLK_SRC_FCK ; 
 int /*<<< orphan*/  DSS_CLK_SRC_PLL1_1 ; 
 int /*<<< orphan*/  DSS_CLK_SRC_PLL2_1 ; 
 int /*<<< orphan*/  DSS_IO_PAD_MODE_BYPASS ; 
 scalar_t__ OMAP_DSS_DSI_CMD_MODE ; 
 int dsi_configure_dispc_clocks (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_framedone_irq_callback ; 
 int /*<<< orphan*/  dsi_get_pixel_size (int /*<<< orphan*/ ) ; 
 int dss_mgr_register_framedone_handler (TYPE_1__*,int /*<<< orphan*/ ,struct dsi_data*) ; 
 int /*<<< orphan*/  dss_mgr_set_lcd_config (TYPE_1__*,TYPE_5__*) ; 
 int /*<<< orphan*/  dss_mgr_set_timings (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  dss_mgr_unregister_framedone_handler (TYPE_1__*,int /*<<< orphan*/ ,struct dsi_data*) ; 
 int /*<<< orphan*/  dss_select_lcd_clk_source (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsi_display_init_dispc(struct dsi_data *dsi)
{
	enum omap_channel channel = dsi->output.dispc_channel;
	int r;

	dss_select_lcd_clk_source(dsi->dss, channel, dsi->module_id == 0 ?
			DSS_CLK_SRC_PLL1_1 :
			DSS_CLK_SRC_PLL2_1);

	if (dsi->mode == OMAP_DSS_DSI_CMD_MODE) {
		r = dss_mgr_register_framedone_handler(&dsi->output,
				dsi_framedone_irq_callback, dsi);
		if (r) {
			DSSERR("can't register FRAMEDONE handler\n");
			goto err;
		}

		dsi->mgr_config.stallmode = true;
		dsi->mgr_config.fifohandcheck = true;
	} else {
		dsi->mgr_config.stallmode = false;
		dsi->mgr_config.fifohandcheck = false;
	}

	/*
	 * override interlace, logic level and edge related parameters in
	 * videomode with default values
	 */
	dsi->vm.flags &= ~DISPLAY_FLAGS_INTERLACED;
	dsi->vm.flags &= ~DISPLAY_FLAGS_HSYNC_LOW;
	dsi->vm.flags |= DISPLAY_FLAGS_HSYNC_HIGH;
	dsi->vm.flags &= ~DISPLAY_FLAGS_VSYNC_LOW;
	dsi->vm.flags |= DISPLAY_FLAGS_VSYNC_HIGH;
	dsi->vm.flags &= ~DISPLAY_FLAGS_PIXDATA_NEGEDGE;
	dsi->vm.flags |= DISPLAY_FLAGS_PIXDATA_POSEDGE;
	dsi->vm.flags &= ~DISPLAY_FLAGS_DE_LOW;
	dsi->vm.flags |= DISPLAY_FLAGS_DE_HIGH;
	dsi->vm.flags &= ~DISPLAY_FLAGS_SYNC_POSEDGE;
	dsi->vm.flags |= DISPLAY_FLAGS_SYNC_NEGEDGE;

	dss_mgr_set_timings(&dsi->output, &dsi->vm);

	r = dsi_configure_dispc_clocks(dsi);
	if (r)
		goto err1;

	dsi->mgr_config.io_pad_mode = DSS_IO_PAD_MODE_BYPASS;
	dsi->mgr_config.video_port_width =
			dsi_get_pixel_size(dsi->pix_fmt);
	dsi->mgr_config.lcden_sig_polarity = 0;

	dss_mgr_set_lcd_config(&dsi->output, &dsi->mgr_config);

	return 0;
err1:
	if (dsi->mode == OMAP_DSS_DSI_CMD_MODE)
		dss_mgr_unregister_framedone_handler(&dsi->output,
				dsi_framedone_irq_callback, dsi);
err:
	dss_select_lcd_clk_source(dsi->dss, channel, DSS_CLK_SRC_FCK);
	return r;
}