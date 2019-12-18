#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mt76x02_sta {int /*<<< orphan*/  wcid; } ;
struct mt76x02_dev {int dummy; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_tx_rate {int /*<<< orphan*/  flags; int /*<<< orphan*/  idx; } ;
struct ieee80211_sta_rates {TYPE_1__* rate; } ;
struct ieee80211_sta {int /*<<< orphan*/  rates; scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct mt76x02_dev* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt76x02_mac_wcid_set_rate (struct mt76x02_dev*,int /*<<< orphan*/ *,struct ieee80211_tx_rate*) ; 
 struct ieee80211_sta_rates* rcu_dereference (int /*<<< orphan*/ ) ; 

void mt76x02_sta_rate_tbl_update(struct ieee80211_hw *hw,
				 struct ieee80211_vif *vif,
				 struct ieee80211_sta *sta)
{
	struct mt76x02_dev *dev = hw->priv;
	struct mt76x02_sta *msta = (struct mt76x02_sta *)sta->drv_priv;
	struct ieee80211_sta_rates *rates = rcu_dereference(sta->rates);
	struct ieee80211_tx_rate rate = {};

	if (!rates)
		return;

	rate.idx = rates->rate[0].idx;
	rate.flags = rates->rate[0].flags;
	mt76x02_mac_wcid_set_rate(dev, &msta->wcid, &rate);
}