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
struct sk_buff {struct sk_buff* next; } ;
struct efx_tx_queue {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_consume_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  efx_enqueue_skb (struct efx_tx_queue*,struct sk_buff*) ; 
 struct sk_buff* skb_gso_segment (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int efx_tx_tso_fallback(struct efx_tx_queue *tx_queue,
			       struct sk_buff *skb)
{
	struct sk_buff *segments, *next;

	segments = skb_gso_segment(skb, 0);
	if (IS_ERR(segments))
		return PTR_ERR(segments);

	dev_consume_skb_any(skb);
	skb = segments;

	while (skb) {
		next = skb->next;
		skb->next = NULL;

		efx_enqueue_skb(tx_queue, skb);
		skb = next;
	}

	return 0;
}