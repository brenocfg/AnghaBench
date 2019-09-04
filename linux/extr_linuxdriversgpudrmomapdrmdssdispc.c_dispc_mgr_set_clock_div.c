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
struct dispc_device {int dummy; } ;
struct dispc_clock_info {int /*<<< orphan*/  pck_div; int /*<<< orphan*/  lck_div; int /*<<< orphan*/  pck; int /*<<< orphan*/  lck; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_mgr_set_lcd_divisor (struct dispc_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dispc_mgr_set_clock_div(struct dispc_device *dispc,
			     enum omap_channel channel,
			     const struct dispc_clock_info *cinfo)
{
	DSSDBG("lck = %lu (%u)\n", cinfo->lck, cinfo->lck_div);
	DSSDBG("pck = %lu (%u)\n", cinfo->pck, cinfo->pck_div);

	dispc_mgr_set_lcd_divisor(dispc, channel, cinfo->lck_div,
				  cinfo->pck_div);
}