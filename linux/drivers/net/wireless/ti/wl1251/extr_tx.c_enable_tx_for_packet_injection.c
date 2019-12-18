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
struct wl1251 {int joined; int /*<<< orphan*/  dtim_period; int /*<<< orphan*/  beacon_int; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSS_TYPE_STA_BSS ; 
 int /*<<< orphan*/  JOIN_EVENT_COMPLETE_ID ; 
 int wl1251_cmd_join (struct wl1251*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wl1251_event_wait (struct wl1251*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wl1251_warning (char*) ; 

__attribute__((used)) static void enable_tx_for_packet_injection(struct wl1251 *wl)
{
	int ret;

	ret = wl1251_cmd_join(wl, BSS_TYPE_STA_BSS, wl->channel,
			      wl->beacon_int, wl->dtim_period);
	if (ret < 0) {
		wl1251_warning("join failed");
		return;
	}

	ret = wl1251_event_wait(wl, JOIN_EVENT_COMPLETE_ID, 100);
	if (ret < 0) {
		wl1251_warning("join timeout");
		return;
	}

	wl->joined = true;
}