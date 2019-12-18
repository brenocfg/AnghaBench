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
typedef  int u32 ;
struct wireless_dev {int /*<<< orphan*/  beacon_interval; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;
struct wiphy {int dummy; } ;
struct wil6210_vif {int privacy; int /*<<< orphan*/  pbss; int /*<<< orphan*/  hidden_ssid; int /*<<< orphan*/  wmi_edmg_channel; int /*<<< orphan*/  channel; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/  mid; } ;
struct wil6210_priv {int dummy; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct cfg80211_beacon_data {int /*<<< orphan*/  tail_len; scalar_t__ tail; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_RSN ; 
 int _wil_cfg80211_set_ies (struct wil6210_vif*,struct cfg80211_beacon_data*) ; 
 int _wil_cfg80211_start_ap (struct wiphy*,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cfg80211_beacon_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cfg80211_find_ie (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wil6210_vif* ndev_to_vif (struct net_device*) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*,int,...) ; 
 int /*<<< orphan*/  wil_print_bcon_data (struct cfg80211_beacon_data*) ; 
 struct wil6210_priv* wiphy_to_wil (struct wiphy*) ; 

__attribute__((used)) static int wil_cfg80211_change_beacon(struct wiphy *wiphy,
				      struct net_device *ndev,
				      struct cfg80211_beacon_data *bcon)
{
	struct wil6210_priv *wil = wiphy_to_wil(wiphy);
	struct wireless_dev *wdev = ndev->ieee80211_ptr;
	struct wil6210_vif *vif = ndev_to_vif(ndev);
	int rc;
	u32 privacy = 0;

	wil_dbg_misc(wil, "change_beacon, mid=%d\n", vif->mid);
	wil_print_bcon_data(bcon);

	if (bcon->tail &&
	    cfg80211_find_ie(WLAN_EID_RSN, bcon->tail,
			     bcon->tail_len))
		privacy = 1;

	memcpy(vif->ssid, wdev->ssid, wdev->ssid_len);
	vif->ssid_len = wdev->ssid_len;

	/* in case privacy has changed, need to restart the AP */
	if (vif->privacy != privacy) {
		wil_dbg_misc(wil, "privacy changed %d=>%d. Restarting AP\n",
			     vif->privacy, privacy);

		rc = _wil_cfg80211_start_ap(wiphy, ndev, vif->ssid,
					    vif->ssid_len, privacy,
					    wdev->beacon_interval,
					    vif->channel,
					    vif->wmi_edmg_channel, bcon,
					    vif->hidden_ssid,
					    vif->pbss);
	} else {
		rc = _wil_cfg80211_set_ies(vif, bcon);
	}

	return rc;
}