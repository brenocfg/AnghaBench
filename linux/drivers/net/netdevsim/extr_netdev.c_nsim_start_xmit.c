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
struct sk_buff {scalar_t__ len; } ;
struct netdevsim {int /*<<< orphan*/  syncp; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct netdevsim* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nsim_ipsec_tx (struct netdevsim*,struct sk_buff*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static netdev_tx_t nsim_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct netdevsim *ns = netdev_priv(dev);

	if (!nsim_ipsec_tx(ns, skb))
		goto out;

	u64_stats_update_begin(&ns->syncp);
	ns->tx_packets++;
	ns->tx_bytes += skb->len;
	u64_stats_update_end(&ns->syncp);

out:
	dev_kfree_skb(skb);

	return NETDEV_TX_OK;
}