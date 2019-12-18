#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct mt76_wcid {int dummy; } ;
struct TYPE_7__ {struct mt76_wcid wcid; } ;
struct mt7603_vif {TYPE_3__ sta; } ;
struct mt7603_sta {struct mt76_wcid wcid; } ;
struct TYPE_6__ {struct mt76_wcid wcid; } ;
struct mt7603_dev {int /*<<< orphan*/  mt76; TYPE_2__ global_sta; } ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct TYPE_5__ {struct ieee80211_vif* vif; } ;
struct ieee80211_tx_info {TYPE_1__ control; } ;
struct ieee80211_tx_control {TYPE_4__* sta; } ;
struct ieee80211_hw {struct mt7603_dev* priv; } ;
struct TYPE_8__ {scalar_t__ drv_priv; } ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  mt76_tx (int /*<<< orphan*/ *,TYPE_4__*,struct mt76_wcid*,struct sk_buff*) ; 

__attribute__((used)) static void mt7603_tx(struct ieee80211_hw *hw,
		      struct ieee80211_tx_control *control,
		      struct sk_buff *skb)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct ieee80211_vif *vif = info->control.vif;
	struct mt7603_dev *dev = hw->priv;
	struct mt76_wcid *wcid = &dev->global_sta.wcid;

	if (control->sta) {
		struct mt7603_sta *msta;

		msta = (struct mt7603_sta *)control->sta->drv_priv;
		wcid = &msta->wcid;
	} else if (vif) {
		struct mt7603_vif *mvif;

		mvif = (struct mt7603_vif *)vif->drv_priv;
		wcid = &mvif->sta.wcid;
	}

	mt76_tx(&dev->mt76, control->sta, wcid, skb);
}