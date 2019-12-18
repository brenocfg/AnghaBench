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
struct xenvif_queue {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* xenvif_rx_dequeue (struct xenvif_queue*) ; 

__attribute__((used)) static void xenvif_rx_queue_purge(struct xenvif_queue *queue)
{
	struct sk_buff *skb;

	while ((skb = xenvif_rx_dequeue(queue)) != NULL)
		kfree_skb(skb);
}