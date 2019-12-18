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
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct napi_struct {int dummy; } ;
struct mt76_dev {int /*<<< orphan*/ * rx_skb; } ;
typedef  enum mt76_rxq_id { ____Placeholder_mt76_rxq_id } mt76_rxq_id ;

/* Variables and functions */
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  mt76_check_sta (struct mt76_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  mt76_rx_aggr_reorder (struct sk_buff*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  mt76_rx_complete (struct mt76_dev*,struct sk_buff_head*,struct napi_struct*) ; 

void mt76_rx_poll_complete(struct mt76_dev *dev, enum mt76_rxq_id q,
			   struct napi_struct *napi)
{
	struct sk_buff_head frames;
	struct sk_buff *skb;

	__skb_queue_head_init(&frames);

	while ((skb = __skb_dequeue(&dev->rx_skb[q])) != NULL) {
		mt76_check_sta(dev, skb);
		mt76_rx_aggr_reorder(skb, &frames);
	}

	mt76_rx_complete(dev, &frames, napi);
}