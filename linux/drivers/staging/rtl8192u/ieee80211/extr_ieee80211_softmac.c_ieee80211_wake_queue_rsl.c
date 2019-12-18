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
struct sk_buff {scalar_t__ data; } ;
struct rtl_80211_hdr_3addr {int /*<<< orphan*/  seq_ctl; } ;
struct TYPE_4__ {int /*<<< orphan*/  swtxawake; } ;
struct TYPE_3__ {scalar_t__ txb; } ;
struct ieee80211_device {int softmac_features; int* seq_ctrl; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; TYPE_2__ softmac_stats; scalar_t__ queue_stop; TYPE_1__ tx_pending; int /*<<< orphan*/  basic_rate; int /*<<< orphan*/  (* softmac_data_hard_start_xmit ) (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int IEEE_SOFTMAC_SINGLE_QUEUE ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 struct sk_buff* dequeue_mgmt (struct ieee80211_device*) ; 
 int /*<<< orphan*/  ieee80211_resume_tx (struct ieee80211_device*) ; 
 scalar_t__ netif_queue_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ieee80211_wake_queue(struct ieee80211_device *ieee)
{
	unsigned long flags;
	struct sk_buff *skb;
	struct rtl_80211_hdr_3addr  *header;

	spin_lock_irqsave(&ieee->lock, flags);
	if (!ieee->queue_stop)
		goto exit;

	ieee->queue_stop = 0;

	if (ieee->softmac_features & IEEE_SOFTMAC_SINGLE_QUEUE) {
		while (!ieee->queue_stop && (skb = dequeue_mgmt(ieee))) {
			header = (struct rtl_80211_hdr_3addr  *)skb->data;

			header->seq_ctl = cpu_to_le16(ieee->seq_ctrl[0] << 4);

			if (ieee->seq_ctrl[0] == 0xFFF)
				ieee->seq_ctrl[0] = 0;
			else
				ieee->seq_ctrl[0]++;

			ieee->softmac_data_hard_start_xmit(skb, ieee->dev, ieee->basic_rate);
			//dev_kfree_skb_any(skb);//edit by thomas
		}
	}
	if (!ieee->queue_stop && ieee->tx_pending.txb)
		ieee80211_resume_tx(ieee);

	if (!ieee->queue_stop && netif_queue_stopped(ieee->dev)) {
		ieee->softmac_stats.swtxawake++;
		netif_wake_queue(ieee->dev);
	}
exit:
	spin_unlock_irqrestore(&ieee->lock, flags);
}