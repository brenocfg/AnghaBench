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
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
 int OMAP_DSS_CHANNEL_DIGIT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dispc_mgr_enable_digit_out () ; 
 int /*<<< orphan*/  dispc_mgr_enable_lcd_out (int) ; 
 scalar_t__ dss_mgr_is_lcd (int) ; 

void dispc_mgr_enable_sync(enum omap_channel channel)
{
	if (dss_mgr_is_lcd(channel))
		dispc_mgr_enable_lcd_out(channel);
	else if (channel == OMAP_DSS_CHANNEL_DIGIT)
		dispc_mgr_enable_digit_out();
	else
		WARN_ON(1);
}