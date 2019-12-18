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
struct pn533 {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_header_len; scalar_t__ tx_tail_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *pn533_alloc_skb(struct pn533 *dev, unsigned int size)
{
	struct sk_buff *skb;

	skb = alloc_skb(dev->ops->tx_header_len +
			size +
			dev->ops->tx_tail_len, GFP_KERNEL);

	if (skb)
		skb_reserve(skb, dev->ops->tx_header_len);

	return skb;
}