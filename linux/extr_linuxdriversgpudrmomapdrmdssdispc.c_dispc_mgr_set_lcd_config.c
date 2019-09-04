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
struct dss_lcd_mgr_config {int /*<<< orphan*/  lcden_sig_polarity; int /*<<< orphan*/  video_port_width; int /*<<< orphan*/  clock_info; int /*<<< orphan*/  fifohandcheck; int /*<<< orphan*/  stallmode; int /*<<< orphan*/  io_pad_mode; } ;
struct dispc_device {int dummy; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
 int /*<<< orphan*/  dispc_lcd_enable_signal_polarity (struct dispc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_mgr_enable_fifohandcheck (struct dispc_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_mgr_enable_stallmode (struct dispc_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_mgr_set_clock_div (struct dispc_device*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dispc_mgr_set_io_pad_mode (struct dispc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_mgr_set_lcd_type_tft (struct dispc_device*,int) ; 
 int /*<<< orphan*/  dispc_mgr_set_tft_data_lines (struct dispc_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispc_mgr_set_lcd_config(struct dispc_device *dispc,
				     enum omap_channel channel,
				     const struct dss_lcd_mgr_config *config)
{
	dispc_mgr_set_io_pad_mode(dispc, config->io_pad_mode);

	dispc_mgr_enable_stallmode(dispc, channel, config->stallmode);
	dispc_mgr_enable_fifohandcheck(dispc, channel, config->fifohandcheck);

	dispc_mgr_set_clock_div(dispc, channel, &config->clock_info);

	dispc_mgr_set_tft_data_lines(dispc, channel, config->video_port_width);

	dispc_lcd_enable_signal_polarity(dispc, config->lcden_sig_polarity);

	dispc_mgr_set_lcd_type_tft(dispc, channel);
}