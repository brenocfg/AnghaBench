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
struct mt76_wcid {int idx; int /*<<< orphan*/ * aggr; } ;
struct mt76_dev {int /*<<< orphan*/  wcid_mask; TYPE_1__* drv; int /*<<< orphan*/ * wcid; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int /*<<< orphan*/ * txq; scalar_t__ drv_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* sta_remove ) (struct mt76_dev*,struct ieee80211_vif*,struct ieee80211_sta*) ;} ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76_rx_aggr_stop (struct mt76_dev*,struct mt76_wcid*,int) ; 
 int /*<<< orphan*/  mt76_tx_status_check (struct mt76_dev*,struct mt76_wcid*,int) ; 
 int /*<<< orphan*/  mt76_txq_remove (struct mt76_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wcid_free (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mt76_dev*,struct ieee80211_vif*,struct ieee80211_sta*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void __mt76_sta_remove(struct mt76_dev *dev, struct ieee80211_vif *vif,
		       struct ieee80211_sta *sta)
{
	struct mt76_wcid *wcid = (struct mt76_wcid *)sta->drv_priv;
	int i, idx = wcid->idx;

	rcu_assign_pointer(dev->wcid[idx], NULL);
	synchronize_rcu();

	for (i = 0; i < ARRAY_SIZE(wcid->aggr); i++)
		mt76_rx_aggr_stop(dev, wcid, i);

	if (dev->drv->sta_remove)
		dev->drv->sta_remove(dev, vif, sta);

	mt76_tx_status_check(dev, wcid, true);
	for (i = 0; i < ARRAY_SIZE(sta->txq); i++)
		mt76_txq_remove(dev, sta->txq[i]);
	mt76_wcid_free(dev->wcid_mask, idx);
}