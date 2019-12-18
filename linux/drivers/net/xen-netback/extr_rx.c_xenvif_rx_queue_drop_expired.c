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
struct xenvif_queue {int /*<<< orphan*/  rx_queue; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  expires; } ;

/* Variables and functions */
 TYPE_1__* XENVIF_RX_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenvif_rx_dequeue (struct xenvif_queue*) ; 

__attribute__((used)) static void xenvif_rx_queue_drop_expired(struct xenvif_queue *queue)
{
	struct sk_buff *skb;

	for (;;) {
		skb = skb_peek(&queue->rx_queue);
		if (!skb)
			break;
		if (time_before(jiffies, XENVIF_RX_CB(skb)->expires))
			break;
		xenvif_rx_dequeue(queue);
		kfree_skb(skb);
	}
}