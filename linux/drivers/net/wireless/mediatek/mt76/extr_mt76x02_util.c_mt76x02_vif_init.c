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
struct TYPE_3__ {int hw_key_idx; int /*<<< orphan*/  idx; } ;
struct mt76x02_vif {unsigned int idx; TYPE_1__ group_wcid; } ;
struct mt76x02_dev {int /*<<< orphan*/  mt76; } ;
struct mt76_txq {TYPE_1__* wcid; } ;
struct ieee80211_vif {TYPE_2__* txq; scalar_t__ drv_priv; } ;
struct TYPE_4__ {scalar_t__ drv_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_VIF_WCID (unsigned int) ; 
 int /*<<< orphan*/  memset (struct mt76x02_vif*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_txq_init (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void
mt76x02_vif_init(struct mt76x02_dev *dev, struct ieee80211_vif *vif,
		 unsigned int idx)
{
	struct mt76x02_vif *mvif = (struct mt76x02_vif *)vif->drv_priv;
	struct mt76_txq *mtxq;

	memset(mvif, 0, sizeof(*mvif));

	mvif->idx = idx;
	mvif->group_wcid.idx = MT_VIF_WCID(idx);
	mvif->group_wcid.hw_key_idx = -1;
	mtxq = (struct mt76_txq *)vif->txq->drv_priv;
	mtxq->wcid = &mvif->group_wcid;

	mt76_txq_init(&dev->mt76, vif->txq);
}