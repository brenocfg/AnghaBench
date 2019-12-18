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
struct brcms_c_info {int /*<<< orphan*/  wiphy; void* radio_timer; int /*<<< orphan*/  wl; void* wdtimer; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcms_c_radio_timer ; 
 int /*<<< orphan*/  brcms_c_watchdog_by_timer ; 
 void* brcms_init_timer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct brcms_c_info*,char*) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static bool brcms_c_timers_init(struct brcms_c_info *wlc, int unit)
{
	wlc->wdtimer = brcms_init_timer(wlc->wl, brcms_c_watchdog_by_timer,
		wlc, "watchdog");
	if (!wlc->wdtimer) {
		wiphy_err(wlc->wiphy, "wl%d:  wl_init_timer for wdtimer "
			  "failed\n", unit);
		goto fail;
	}

	wlc->radio_timer = brcms_init_timer(wlc->wl, brcms_c_radio_timer,
		wlc, "radio");
	if (!wlc->radio_timer) {
		wiphy_err(wlc->wiphy, "wl%d:  wl_init_timer for radio_timer "
			  "failed\n", unit);
		goto fail;
	}

	return true;

 fail:
	return false;
}