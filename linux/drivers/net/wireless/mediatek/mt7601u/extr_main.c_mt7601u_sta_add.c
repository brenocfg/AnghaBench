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
struct mt76_vif {int /*<<< orphan*/  idx; } ;
struct TYPE_2__ {int idx; int hw_key_idx; } ;
struct mt76_sta {TYPE_1__ wcid; } ;
struct mt7601u_dev {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * wcid; } ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct mt7601u_dev* priv; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  MT_WCID_DROP (int) ; 
 int /*<<< orphan*/  MT_WCID_DROP_MASK (int) ; 
 int /*<<< orphan*/  mt7601u_mac_set_ampdu_factor (struct mt7601u_dev*) ; 
 int /*<<< orphan*/  mt7601u_mac_wcid_setup (struct mt7601u_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_clear (struct mt7601u_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mt76_wcid_alloc (struct mt7601u_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int
mt7601u_sta_add(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
		struct ieee80211_sta *sta)
{
	struct mt7601u_dev *dev = hw->priv;
	struct mt76_sta *msta = (struct mt76_sta *) sta->drv_priv;
	struct mt76_vif *mvif = (struct mt76_vif *) vif->drv_priv;
	int ret = 0;
	int idx = 0;

	mutex_lock(&dev->mutex);

	idx = mt76_wcid_alloc(dev);
	if (idx < 0) {
		ret = -ENOSPC;
		goto out;
	}

	msta->wcid.idx = idx;
	msta->wcid.hw_key_idx = -1;
	mt7601u_mac_wcid_setup(dev, idx, mvif->idx, sta->addr);
	mt76_clear(dev, MT_WCID_DROP(idx), MT_WCID_DROP_MASK(idx));
	rcu_assign_pointer(dev->wcid[idx], &msta->wcid);
	mt7601u_mac_set_ampdu_factor(dev);

out:
	mutex_unlock(&dev->mutex);

	return ret;
}