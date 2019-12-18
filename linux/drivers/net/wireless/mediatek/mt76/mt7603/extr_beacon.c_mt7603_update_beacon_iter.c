#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct TYPE_10__ {int idx; } ;
struct TYPE_6__ {TYPE_5__ wcid; } ;
struct mt7603_vif {TYPE_1__ sta; int /*<<< orphan*/  idx; } ;
struct TYPE_9__ {int beacon_mask; TYPE_3__* q_tx; } ;
struct mt7603_dev {int /*<<< orphan*/  ps_lock; int /*<<< orphan*/  beacon_check; TYPE_4__ mt76; } ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct TYPE_8__ {TYPE_2__* q; } ;
struct TYPE_7__ {int hw_idx; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT7603_WATCHDOG_TIMEOUT ; 
 int /*<<< orphan*/  MT_DMA_FQCR0 ; 
 int MT_DMA_FQCR0_BUSY ; 
 int /*<<< orphan*/  MT_DMA_FQCR0_DEST_PORT_ID ; 
 int /*<<< orphan*/  MT_DMA_FQCR0_DEST_QUEUE_ID ; 
 int /*<<< orphan*/  MT_DMA_FQCR0_TARGET_QID ; 
 int /*<<< orphan*/  MT_DMA_FQCR0_TARGET_WCID ; 
 int /*<<< orphan*/  MT_TXQ_BEACON ; 
 size_t MT_TXQ_CAB ; 
 struct sk_buff* ieee80211_beacon_get (int /*<<< orphan*/ ,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  mt76_hw (struct mt7603_dev*) ; 
 int /*<<< orphan*/  mt76_poll (struct mt7603_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_tx_queue_skb (struct mt7603_dev*,int /*<<< orphan*/ ,struct sk_buff*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76_wr (struct mt7603_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mt7603_update_beacon_iter(void *priv, u8 *mac, struct ieee80211_vif *vif)
{
	struct mt7603_dev *dev = (struct mt7603_dev *)priv;
	struct mt7603_vif *mvif = (struct mt7603_vif *)vif->drv_priv;
	struct sk_buff *skb = NULL;

	if (!(dev->mt76.beacon_mask & BIT(mvif->idx)))
		return;

	skb = ieee80211_beacon_get(mt76_hw(dev), vif);
	if (!skb)
		return;

	mt76_tx_queue_skb(dev, MT_TXQ_BEACON, skb, &mvif->sta.wcid, NULL);

	spin_lock_bh(&dev->ps_lock);
	mt76_wr(dev, MT_DMA_FQCR0, MT_DMA_FQCR0_BUSY |
		FIELD_PREP(MT_DMA_FQCR0_TARGET_WCID, mvif->sta.wcid.idx) |
		FIELD_PREP(MT_DMA_FQCR0_TARGET_QID,
			   dev->mt76.q_tx[MT_TXQ_CAB].q->hw_idx) |
		FIELD_PREP(MT_DMA_FQCR0_DEST_PORT_ID, 3) |
		FIELD_PREP(MT_DMA_FQCR0_DEST_QUEUE_ID, 8));

	if (!mt76_poll(dev, MT_DMA_FQCR0, MT_DMA_FQCR0_BUSY, 0, 5000))
		dev->beacon_check = MT7603_WATCHDOG_TIMEOUT;

	spin_unlock_bh(&dev->ps_lock);
}