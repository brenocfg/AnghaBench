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
struct mt76x02_dev {int dummy; } ;
struct mt76_wcid {scalar_t__ hw_key_idx; int /*<<< orphan*/  idx; scalar_t__ sw_iv; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct ieee80211_key_conf {scalar_t__ keyidx; } ;
struct ieee80211_hw {struct mt76x02_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt76x02_mac_wcid_sync_pn (struct mt76x02_dev*,int /*<<< orphan*/ ,struct ieee80211_key_conf*) ; 

__attribute__((used)) static void mt76x02_key_sync(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
			     struct ieee80211_sta *sta,
			     struct ieee80211_key_conf *key, void *data)
{
	struct mt76x02_dev *dev = hw->priv;
	struct mt76_wcid *wcid;

	if (!sta)
		return;

	wcid = (struct mt76_wcid *)sta->drv_priv;

	if (wcid->hw_key_idx != key->keyidx || wcid->sw_iv)
		return;

	mt76x02_mac_wcid_sync_pn(dev, wcid->idx, key);
}