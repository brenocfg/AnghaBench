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
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_consume_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_complete_wifi_ack (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_need_txstat (struct sk_buff*) ; 

__attribute__((used)) static inline void wil_consume_skb(struct sk_buff *skb, bool acked)
{
	if (unlikely(wil_need_txstat(skb)))
		skb_complete_wifi_ack(skb, acked);
	else
		acked ? dev_consume_skb_any(skb) : dev_kfree_skb_any(skb);
}