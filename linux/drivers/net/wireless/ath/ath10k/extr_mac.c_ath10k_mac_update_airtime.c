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
typedef  int u32 ;
typedef  int u16 ;
struct sk_buff {int len; } ;
struct ieee80211_txq {TYPE_2__* sta; } ;
struct ath10k_sta {int last_tx_bitrate; } ;
struct TYPE_3__ {int /*<<< orphan*/  svc_map; } ;
struct ath10k {int /*<<< orphan*/  data_lock; TYPE_1__ wmi; } ;
struct TYPE_4__ {scalar_t__ drv_priv; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_ATF_OVERHEAD ; 
 scalar_t__ IEEE80211_ATF_OVERHEAD_IFS ; 
 int /*<<< orphan*/  WMI_SERVICE_REPORT_AIRTIME ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 ath10k_mac_update_airtime(struct ath10k *ar,
				     struct ieee80211_txq *txq,
				     struct sk_buff *skb)
{
	struct ath10k_sta *arsta;
	u32 pktlen;
	u16 airtime = 0;

	if (!txq || !txq->sta)
		return airtime;

	if (test_bit(WMI_SERVICE_REPORT_AIRTIME, ar->wmi.svc_map))
		return airtime;

	spin_lock_bh(&ar->data_lock);
	arsta = (struct ath10k_sta *)txq->sta->drv_priv;

	pktlen = skb->len + 38; /* Assume MAC header 30, SNAP 8 for most case */
	if (arsta->last_tx_bitrate) {
		/* airtime in us, last_tx_bitrate in 100kbps */
		airtime = (pktlen * 8 * (1000 / 100))
				/ arsta->last_tx_bitrate;
		/* overhead for media access time and IFS */
		airtime += IEEE80211_ATF_OVERHEAD_IFS;
	} else {
		/* This is mostly for throttle excessive BC/MC frames, and the
		 * airtime/rate doesn't need be exact. Airtime of BC/MC frames
		 * in 2G get some discount, which helps prevent very low rate
		 * frames from being blocked for too long.
		 */
		airtime = (pktlen * 8 * (1000 / 100)) / 60; /* 6M */
		airtime += IEEE80211_ATF_OVERHEAD;
	}
	spin_unlock_bh(&ar->data_lock);

	return airtime;
}