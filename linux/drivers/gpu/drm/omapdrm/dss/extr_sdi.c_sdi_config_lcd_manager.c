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
struct TYPE_2__ {int stallmode; int fifohandcheck; int video_port_width; int lcden_sig_polarity; int /*<<< orphan*/  io_pad_mode; } ;
struct sdi_device {TYPE_1__ mgr_config; int /*<<< orphan*/  output; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSS_IO_PAD_MODE_BYPASS ; 
 int /*<<< orphan*/  dss_mgr_set_lcd_config (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void sdi_config_lcd_manager(struct sdi_device *sdi)
{
	sdi->mgr_config.io_pad_mode = DSS_IO_PAD_MODE_BYPASS;

	sdi->mgr_config.stallmode = false;
	sdi->mgr_config.fifohandcheck = false;

	sdi->mgr_config.video_port_width = 24;
	sdi->mgr_config.lcden_sig_polarity = 1;

	dss_mgr_set_lcd_config(&sdi->output, &sdi->mgr_config);
}