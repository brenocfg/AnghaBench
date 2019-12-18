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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct wireless_dev {int dummy; } ;
struct wiphy {int dummy; } ;
struct ieee80211_mgmt {int /*<<< orphan*/  frame_control; } ;
struct ieee80211_channel {scalar_t__ center_freq; } ;
struct cfg80211_mgmt_tx_params {size_t len; unsigned int wait; int no_cck; int /*<<< orphan*/ * buf; struct ieee80211_channel* chan; } ;
struct ath6kl_vif {scalar_t__ ch_hint; scalar_t__ nw_type; int /*<<< orphan*/  fw_vif_idx; int /*<<< orphan*/  send_action_id; int /*<<< orphan*/  flags; int /*<<< orphan*/  ndev; } ;
struct ath6kl {int /*<<< orphan*/  wmi; } ;

/* Variables and functions */
 scalar_t__ AP_NETWORK ; 
 int /*<<< orphan*/  CONNECTED ; 
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ ath6kl_is_p2p_go_ssid (int /*<<< orphan*/  const*,size_t) ; 
 int ath6kl_mgmt_powersave_ap (struct ath6kl_vif*,scalar_t__,scalar_t__,unsigned int,int /*<<< orphan*/  const*,size_t,int*,int) ; 
 struct ath6kl* ath6kl_priv (int /*<<< orphan*/ ) ; 
 int ath6kl_send_go_probe_resp (struct ath6kl_vif*,int /*<<< orphan*/  const*,size_t,scalar_t__) ; 
 struct ath6kl_vif* ath6kl_vif_from_wdev (struct wireless_dev*) ; 
 int ath6kl_wmi_send_mgmt_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,unsigned int,int /*<<< orphan*/  const*,size_t,int) ; 
 scalar_t__ ieee80211_is_probe_resp (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath6kl_mgmt_tx(struct wiphy *wiphy, struct wireless_dev *wdev,
			  struct cfg80211_mgmt_tx_params *params, u64 *cookie)
{
	struct ath6kl_vif *vif = ath6kl_vif_from_wdev(wdev);
	struct ath6kl *ar = ath6kl_priv(vif->ndev);
	struct ieee80211_channel *chan = params->chan;
	const u8 *buf = params->buf;
	size_t len = params->len;
	unsigned int wait = params->wait;
	bool no_cck = params->no_cck;
	u32 id, freq;
	const struct ieee80211_mgmt *mgmt;
	bool more_data, queued;

	/* default to the current channel, but use the one specified as argument
	 * if any
	 */
	freq = vif->ch_hint;
	if (chan)
		freq = chan->center_freq;

	/* never send freq zero to the firmware */
	if (WARN_ON(freq == 0))
		return -EINVAL;

	mgmt = (const struct ieee80211_mgmt *) buf;
	if (vif->nw_type == AP_NETWORK && test_bit(CONNECTED, &vif->flags) &&
	    ieee80211_is_probe_resp(mgmt->frame_control) &&
	    ath6kl_is_p2p_go_ssid(buf, len)) {
		/*
		 * Send Probe Response frame in GO mode using a separate WMI
		 * command to allow the target to fill in the generic IEs.
		 */
		*cookie = 0; /* TX status not supported */
		return ath6kl_send_go_probe_resp(vif, buf, len, freq);
	}

	id = vif->send_action_id++;
	if (id == 0) {
		/*
		 * 0 is a reserved value in the WMI command and shall not be
		 * used for the command.
		 */
		id = vif->send_action_id++;
	}

	*cookie = id;

	/* AP mode Power saving processing */
	if (vif->nw_type == AP_NETWORK) {
		queued = ath6kl_mgmt_powersave_ap(vif, id, freq, wait, buf, len,
						  &more_data, no_cck);
		if (queued)
			return 0;
	}

	return ath6kl_wmi_send_mgmt_cmd(ar->wmi, vif->fw_vif_idx, id, freq,
					wait, buf, len, no_cck);
}