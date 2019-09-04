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
struct sk_buff {int dummy; } ;
struct chtls_sock {struct sk_buff* wr_skb_tail; struct sk_buff* wr_skb_head; } ;
struct TYPE_2__ {struct sk_buff* next_wr; } ;

/* Variables and functions */
 TYPE_1__* WR_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_get (struct sk_buff*) ; 

__attribute__((used)) static inline void enqueue_wr(struct chtls_sock *csk, struct sk_buff *skb)
{
	WR_SKB_CB(skb)->next_wr = NULL;

	skb_get(skb);

	if (!csk->wr_skb_head)
		csk->wr_skb_head = skb;
	else
		WR_SKB_CB(csk->wr_skb_tail)->next_wr = skb;
	csk->wr_skb_tail = skb;
}