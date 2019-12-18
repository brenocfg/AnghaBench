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
struct wiphy {int dummy; } ;
struct wil6210_vif {scalar_t__ ssid_len; scalar_t__ gtk_len; int /*<<< orphan*/  gtk_index; int /*<<< orphan*/  gtk; int /*<<< orphan*/  privacy; int /*<<< orphan*/  pbss; int /*<<< orphan*/  hidden_ssid; int /*<<< orphan*/  wmi_edmg_channel; int /*<<< orphan*/  channel; int /*<<< orphan*/  bi; int /*<<< orphan*/  ssid; int /*<<< orphan*/  proberesp_len; int /*<<< orphan*/  assocresp_ies_len; int /*<<< orphan*/  proberesp_ies_len; int /*<<< orphan*/  proberesp; int /*<<< orphan*/  assocresp_ies; int /*<<< orphan*/  proberesp_ies; } ;
struct wil6210_priv {struct wil6210_vif** vifs; } ;
struct net_device {int dummy; } ;
struct key_params {scalar_t__ key_len; int /*<<< orphan*/  seq_len; int /*<<< orphan*/  key; } ;
struct cfg80211_beacon_data {int /*<<< orphan*/  probe_resp_len; int /*<<< orphan*/  assocresp_ies_len; int /*<<< orphan*/  proberesp_ies_len; int /*<<< orphan*/  probe_resp; int /*<<< orphan*/  assocresp_ies; int /*<<< orphan*/  proberesp_ies; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int GET_MAX_VIFS (struct wil6210_priv*) ; 
 int /*<<< orphan*/  IEEE80211_GCMP_PN_LEN ; 
 int _wil_cfg80211_start_ap (struct wiphy*,struct net_device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cfg80211_beacon_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_device* vif_to_ndev (struct wil6210_vif*) ; 
 int wil_cfg80211_add_key (struct wiphy*,struct net_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,struct key_params*) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*,int,int) ; 
 int /*<<< orphan*/  wil_hex_dump_misc (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  wil_info (struct wil6210_priv*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wiphy* wil_to_wiphy (struct wil6210_priv*) ; 

void wil_cfg80211_ap_recovery(struct wil6210_priv *wil)
{
	int rc, i;
	struct wiphy *wiphy = wil_to_wiphy(wil);

	for (i = 0; i < GET_MAX_VIFS(wil); i++) {
		struct wil6210_vif *vif = wil->vifs[i];
		struct net_device *ndev;
		struct cfg80211_beacon_data bcon = {};
		struct key_params key_params = {};

		if (!vif || vif->ssid_len == 0)
			continue;

		ndev = vif_to_ndev(vif);
		bcon.proberesp_ies = vif->proberesp_ies;
		bcon.assocresp_ies = vif->assocresp_ies;
		bcon.probe_resp = vif->proberesp;
		bcon.proberesp_ies_len = vif->proberesp_ies_len;
		bcon.assocresp_ies_len = vif->assocresp_ies_len;
		bcon.probe_resp_len = vif->proberesp_len;

		wil_info(wil,
			 "AP (vif %d) recovery: privacy %d, bi %d, channel %d, hidden %d, pbss %d\n",
			 i, vif->privacy, vif->bi, vif->channel,
			 vif->hidden_ssid, vif->pbss);
		wil_hex_dump_misc("SSID ", DUMP_PREFIX_OFFSET, 16, 1,
				  vif->ssid, vif->ssid_len, true);
		rc = _wil_cfg80211_start_ap(wiphy, ndev,
					    vif->ssid, vif->ssid_len,
					    vif->privacy, vif->bi,
					    vif->channel,
					    vif->wmi_edmg_channel, &bcon,
					    vif->hidden_ssid, vif->pbss);
		if (rc) {
			wil_err(wil, "vif %d recovery failed (%d)\n", i, rc);
			continue;
		}

		if (!vif->privacy || vif->gtk_len == 0)
			continue;

		key_params.key = vif->gtk;
		key_params.key_len = vif->gtk_len;
		key_params.seq_len = IEEE80211_GCMP_PN_LEN;
		rc = wil_cfg80211_add_key(wiphy, ndev, vif->gtk_index, false,
					  NULL, &key_params);
		if (rc)
			wil_err(wil, "vif %d recovery add key failed (%d)\n",
				i, rc);
	}
}