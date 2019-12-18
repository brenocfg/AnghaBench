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
struct emac_instance {int /*<<< orphan*/  rx_skb_size; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __emac_prepare_rx_skb (struct sk_buff*,struct emac_instance*,int) ; 
 struct sk_buff* __netdev_alloc_skb_ip_align (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
emac_alloc_rx_skb(struct emac_instance *dev, int slot)
{
	struct sk_buff *skb;

	skb = __netdev_alloc_skb_ip_align(dev->ndev, dev->rx_skb_size,
					  GFP_KERNEL);

	return __emac_prepare_rx_skb(skb, dev, slot);
}