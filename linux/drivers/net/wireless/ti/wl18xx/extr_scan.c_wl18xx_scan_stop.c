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
struct wl12xx_vif {int dummy; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCAN_TYPE_SEARCH ; 
 int __wl18xx_scan_stop (struct wl1271*,struct wl12xx_vif*,int /*<<< orphan*/ ) ; 

int wl18xx_scan_stop(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	return __wl18xx_scan_stop(wl, wlvif, SCAN_TYPE_SEARCH);
}