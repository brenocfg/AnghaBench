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
struct sk_buff {int /*<<< orphan*/  csum; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  protocol; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  dev_consume_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void copy_old_skb(struct sk_buff *old, struct sk_buff *skb)
{
	skb->dev = old->dev;
	skb->protocol = old->protocol;
	skb->ip_summed = old->ip_summed;
	skb->csum = old->csum;
	skb_set_network_header(skb, ETH_HLEN);

	dev_consume_skb_any(old);
}