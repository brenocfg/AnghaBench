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
struct wl1271 {int quirks; } ;

/* Variables and functions */
 int WLCORE_QUIRK_FWLOG_NOT_IMPLEMENTED ; 
 int wl12xx_cmd_config_fwlog (struct wl1271*) ; 

__attribute__((used)) static int wl12xx_init_fwlog(struct wl1271 *wl)
{
	int ret;

	if (wl->quirks & WLCORE_QUIRK_FWLOG_NOT_IMPLEMENTED)
		return 0;

	ret = wl12xx_cmd_config_fwlog(wl);
	if (ret < 0)
		return ret;

	return 0;
}