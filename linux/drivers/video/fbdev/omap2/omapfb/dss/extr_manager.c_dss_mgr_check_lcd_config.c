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
struct omap_overlay_manager {int dummy; } ;
struct dispc_clock_info {int lck_div; int pck_div; } ;
struct dss_lcd_mgr_config {int video_port_width; int stallmode; int fifohandcheck; struct dispc_clock_info clock_info; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int dss_mgr_check_lcd_config(struct omap_overlay_manager *mgr,
		const struct dss_lcd_mgr_config *config)
{
	struct dispc_clock_info cinfo = config->clock_info;
	int dl = config->video_port_width;
	bool stallmode = config->stallmode;
	bool fifohandcheck = config->fifohandcheck;

	if (cinfo.lck_div < 1 || cinfo.lck_div > 255)
		return -EINVAL;

	if (cinfo.pck_div < 1 || cinfo.pck_div > 255)
		return -EINVAL;

	if (dl != 12 && dl != 16 && dl != 18 && dl != 24)
		return -EINVAL;

	/* fifohandcheck should be used only with stallmode */
	if (!stallmode && fifohandcheck)
		return -EINVAL;

	/*
	 * io pad mode can be only checked by using dssdev connected to the
	 * manager. Ignore checking these for now, add checks when manager
	 * is capable of holding information related to the connected interface
	 */

	return 0;
}