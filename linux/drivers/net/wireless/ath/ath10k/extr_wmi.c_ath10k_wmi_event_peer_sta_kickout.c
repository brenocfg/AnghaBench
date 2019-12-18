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
struct wmi_peer_kick_ev_arg {int mac_addr; } ;
struct sk_buff {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct ath10k {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int ath10k_wmi_pull_peer_kick (struct ath10k*,struct sk_buff*,struct wmi_peer_kick_ev_arg*) ; 
 struct ieee80211_sta* ieee80211_find_sta_by_ifaddr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_report_low_ack (struct ieee80211_sta*,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

void ath10k_wmi_event_peer_sta_kickout(struct ath10k *ar, struct sk_buff *skb)
{
	struct wmi_peer_kick_ev_arg arg = {};
	struct ieee80211_sta *sta;
	int ret;

	ret = ath10k_wmi_pull_peer_kick(ar, skb, &arg);
	if (ret) {
		ath10k_warn(ar, "failed to parse peer kickout event: %d\n",
			    ret);
		return;
	}

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi event peer sta kickout %pM\n",
		   arg.mac_addr);

	rcu_read_lock();

	sta = ieee80211_find_sta_by_ifaddr(ar->hw, arg.mac_addr, NULL);
	if (!sta) {
		ath10k_warn(ar, "Spurious quick kickout for STA %pM\n",
			    arg.mac_addr);
		goto exit;
	}

	ieee80211_report_low_ack(sta, 10);

exit:
	rcu_read_unlock();
}