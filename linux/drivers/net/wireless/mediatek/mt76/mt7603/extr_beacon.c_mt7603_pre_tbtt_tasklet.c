#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct mt76_queue {scalar_t__ queued; int /*<<< orphan*/  lock; } ;
struct TYPE_10__ {int /*<<< orphan*/  wcid; } ;
struct mt7603_vif {TYPE_3__ sta; } ;
struct TYPE_13__ {int /*<<< orphan*/  beacon_mask; TYPE_4__* q_tx; scalar_t__ csa_complete; } ;
struct mt7603_dev {int* tail; int* count; int /*<<< orphan*/  beacon_check; TYPE_6__ mt76; int /*<<< orphan*/  q; struct mt7603_dev* dev; } ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct TYPE_9__ {struct ieee80211_vif* vif; } ;
struct ieee80211_tx_info {TYPE_2__ control; } ;
struct beacon_bc_data {int* tail; int* count; int /*<<< orphan*/  beacon_check; TYPE_6__ mt76; int /*<<< orphan*/  q; struct beacon_bc_data* dev; } ;
struct TYPE_8__ {int flags; } ;
struct TYPE_12__ {TYPE_1__ conf; } ;
struct TYPE_11__ {struct mt76_queue* q; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int GENMASK (int,int) ; 
 int IEEE80211_CONF_OFFCHANNEL ; 
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_RESUME_ALL ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int MT7603_MAX_INTERFACES ; 
 size_t MT_TXQ_BEACON ; 
 size_t MT_TXQ_CAB ; 
 int /*<<< orphan*/  MT_WF_ARB_CAB_COUNT_B0_REG (int) ; 
 int MT_WF_ARB_CAB_COUNT_B0_SHIFT (int) ; 
 int /*<<< orphan*/  MT_WF_ARB_CAB_FLUSH ; 
 int /*<<< orphan*/  MT_WF_ARB_CAB_START ; 
 int MT_WF_ARB_CAB_START_BSS0n (int) ; 
 int MT_WF_ARB_CAB_START_BSSn (int /*<<< orphan*/ ) ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __skb_queue_head_init (int /*<<< orphan*/ *) ; 
 scalar_t__ hweight8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mt7603_dev*) ; 
 int /*<<< orphan*/  mt7603_add_buffered_bc ; 
 int /*<<< orphan*/  mt7603_update_beacon_iter ; 
 int /*<<< orphan*/  mt76_csa_check (TYPE_6__*) ; 
 TYPE_5__* mt76_hw (struct mt7603_dev*) ; 
 int /*<<< orphan*/  mt76_queue_kick (struct mt7603_dev*,struct mt76_queue*) ; 
 int /*<<< orphan*/  mt76_queue_tx_cleanup (struct mt7603_dev*,size_t,int) ; 
 int /*<<< orphan*/  mt76_skb_set_moredata (int,int) ; 
 int /*<<< orphan*/  mt76_tx_queue_skb (struct mt7603_dev*,size_t,struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76_wr (struct mt7603_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 
 int skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void mt7603_pre_tbtt_tasklet(unsigned long arg)
{
	struct mt7603_dev *dev = (struct mt7603_dev *)arg;
	struct mt76_queue *q;
	struct beacon_bc_data data = {};
	struct sk_buff *skb;
	int i, nframes;

	if (mt76_hw(dev)->conf.flags & IEEE80211_CONF_OFFCHANNEL)
		return;

	data.dev = dev;
	__skb_queue_head_init(&data.q);

	q = dev->mt76.q_tx[MT_TXQ_BEACON].q;
	spin_lock_bh(&q->lock);
	ieee80211_iterate_active_interfaces_atomic(mt76_hw(dev),
		IEEE80211_IFACE_ITER_RESUME_ALL,
		mt7603_update_beacon_iter, dev);
	mt76_queue_kick(dev, q);
	spin_unlock_bh(&q->lock);

	/* Flush all previous CAB queue packets */
	mt76_wr(dev, MT_WF_ARB_CAB_FLUSH, GENMASK(30, 16) | BIT(0));

	mt76_queue_tx_cleanup(dev, MT_TXQ_CAB, false);

	mt76_csa_check(&dev->mt76);
	if (dev->mt76.csa_complete)
		goto out;

	q = dev->mt76.q_tx[MT_TXQ_CAB].q;
	do {
		nframes = skb_queue_len(&data.q);
		ieee80211_iterate_active_interfaces_atomic(mt76_hw(dev),
			IEEE80211_IFACE_ITER_RESUME_ALL,
			mt7603_add_buffered_bc, &data);
	} while (nframes != skb_queue_len(&data.q) &&
		 skb_queue_len(&data.q) < 8);

	if (skb_queue_empty(&data.q))
		goto out;

	for (i = 0; i < ARRAY_SIZE(data.tail); i++) {
		if (!data.tail[i])
			continue;

		mt76_skb_set_moredata(data.tail[i], false);
	}

	spin_lock_bh(&q->lock);
	while ((skb = __skb_dequeue(&data.q)) != NULL) {
		struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
		struct ieee80211_vif *vif = info->control.vif;
		struct mt7603_vif *mvif = (struct mt7603_vif *)vif->drv_priv;

		mt76_tx_queue_skb(dev, MT_TXQ_CAB, skb, &mvif->sta.wcid, NULL);
	}
	mt76_queue_kick(dev, q);
	spin_unlock_bh(&q->lock);

	for (i = 0; i < ARRAY_SIZE(data.count); i++)
		mt76_wr(dev, MT_WF_ARB_CAB_COUNT_B0_REG(i),
			data.count[i] << MT_WF_ARB_CAB_COUNT_B0_SHIFT(i));

	mt76_wr(dev, MT_WF_ARB_CAB_START,
		MT_WF_ARB_CAB_START_BSSn(0) |
		(MT_WF_ARB_CAB_START_BSS0n(1) *
		 ((1 << (MT7603_MAX_INTERFACES - 1)) - 1)));

out:
	mt76_queue_tx_cleanup(dev, MT_TXQ_BEACON, false);
	if (dev->mt76.q_tx[MT_TXQ_BEACON].q->queued >
	    hweight8(dev->mt76.beacon_mask))
		dev->beacon_check++;
}