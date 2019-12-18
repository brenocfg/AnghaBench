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
struct ioc3_private {scalar_t__ tx_ci; scalar_t__ tx_pi; TYPE_1__* txr; struct sk_buff** tx_skbs; } ;
struct TYPE_2__ {scalar_t__ cmd; } ;

/* Variables and functions */
 int TX_RING_ENTRIES ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  ioc3_tx_unmap (struct ioc3_private*,int) ; 

__attribute__((used)) static inline void ioc3_clean_tx_ring(struct ioc3_private *ip)
{
	struct sk_buff *skb;
	int i;

	for (i = 0; i < TX_RING_ENTRIES; i++) {
		skb = ip->tx_skbs[i];
		if (skb) {
			ioc3_tx_unmap(ip, i);
			ip->tx_skbs[i] = NULL;
			dev_kfree_skb_any(skb);
		}
		ip->txr[i].cmd = 0;
	}
	ip->tx_pi = 0;
	ip->tx_ci = 0;
}