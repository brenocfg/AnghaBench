#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mt7615_sta {int n_rates; int rate_probe; TYPE_3__* rates; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct mt7615_dev {TYPE_2__ mt76; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta_rates {TYPE_1__* rate; } ;
struct ieee80211_sta {int /*<<< orphan*/  rates; scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct mt7615_dev* priv; } ;
struct TYPE_7__ {scalar_t__ idx; int /*<<< orphan*/  count; int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {scalar_t__ idx; int /*<<< orphan*/  flags; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 int /*<<< orphan*/  mt7615_mac_set_rates (struct mt7615_dev*,struct mt7615_sta*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 struct ieee80211_sta_rates* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mt7615_sta_rate_tbl_update(struct ieee80211_hw *hw,
				       struct ieee80211_vif *vif,
				       struct ieee80211_sta *sta)
{
	struct mt7615_dev *dev = hw->priv;
	struct mt7615_sta *msta = (struct mt7615_sta *)sta->drv_priv;
	struct ieee80211_sta_rates *sta_rates = rcu_dereference(sta->rates);
	int i;

	spin_lock_bh(&dev->mt76.lock);
	for (i = 0; i < ARRAY_SIZE(msta->rates); i++) {
		msta->rates[i].idx = sta_rates->rate[i].idx;
		msta->rates[i].count = sta_rates->rate[i].count;
		msta->rates[i].flags = sta_rates->rate[i].flags;

		if (msta->rates[i].idx < 0 || !msta->rates[i].count)
			break;
	}
	msta->n_rates = i;
	mt7615_mac_set_rates(dev, msta, NULL, msta->rates);
	msta->rate_probe = false;
	spin_unlock_bh(&dev->mt76.lock);
}