#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wl12xx_vif {int dummy; } ;
struct TYPE_3__ {scalar_t__ state; size_t ssid_len; int failed; int /*<<< orphan*/  scanned_ch; struct cfg80211_scan_request* req; int /*<<< orphan*/  ssid; } ;
struct wl1271 {TYPE_2__* ops; int /*<<< orphan*/  scan_complete_work; int /*<<< orphan*/  hw; TYPE_1__ scan; struct wl12xx_vif* scan_wlvif; } ;
struct ieee80211_vif {int dummy; } ;
struct cfg80211_scan_request {scalar_t__ n_channels; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* scan_start ) (struct wl1271*,struct wl12xx_vif*,struct cfg80211_scan_request*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EBUSY ; 
 scalar_t__ WL1271_MAX_CHANNELS ; 
 scalar_t__ WL1271_SCAN_STATE_2GHZ_ACTIVE ; 
 scalar_t__ WL1271_SCAN_STATE_IDLE ; 
 int /*<<< orphan*/  WL1271_SCAN_TIMEOUT ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct wl1271*,struct wl12xx_vif*,struct cfg80211_scan_request*) ; 
 struct wl12xx_vif* wl12xx_vif_to_data (struct ieee80211_vif*) ; 

int wlcore_scan(struct wl1271 *wl, struct ieee80211_vif *vif,
		const u8 *ssid, size_t ssid_len,
		struct cfg80211_scan_request *req)
{
	struct wl12xx_vif *wlvif = wl12xx_vif_to_data(vif);

	/*
	 * cfg80211 should guarantee that we don't get more channels
	 * than what we have registered.
	 */
	BUG_ON(req->n_channels > WL1271_MAX_CHANNELS);

	if (wl->scan.state != WL1271_SCAN_STATE_IDLE)
		return -EBUSY;

	wl->scan.state = WL1271_SCAN_STATE_2GHZ_ACTIVE;

	if (ssid_len && ssid) {
		wl->scan.ssid_len = ssid_len;
		memcpy(wl->scan.ssid, ssid, ssid_len);
	} else {
		wl->scan.ssid_len = 0;
	}

	wl->scan_wlvif = wlvif;
	wl->scan.req = req;
	memset(wl->scan.scanned_ch, 0, sizeof(wl->scan.scanned_ch));

	/* we assume failure so that timeout scenarios are handled correctly */
	wl->scan.failed = true;
	ieee80211_queue_delayed_work(wl->hw, &wl->scan_complete_work,
				     msecs_to_jiffies(WL1271_SCAN_TIMEOUT));

	wl->ops->scan_start(wl, wlvif, req);

	return 0;
}