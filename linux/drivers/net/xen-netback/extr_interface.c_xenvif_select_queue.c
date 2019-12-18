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
typedef  unsigned int u16 ;
struct TYPE_2__ {unsigned int size; scalar_t__ alg; unsigned int** mapping; size_t mapping_sel; } ;
struct xenvif {TYPE_1__ hash; int /*<<< orphan*/  num_queues; } ;
struct sk_buff {int dummy; } ;
struct net_device {unsigned int real_num_tx_queues; } ;

/* Variables and functions */
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ XEN_NETIF_CTRL_HASH_ALGORITHM_NONE ; 
 unsigned int netdev_pick_tx (struct net_device*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 struct xenvif* netdev_priv (struct net_device*) ; 
 unsigned int skb_get_hash_raw (struct sk_buff*) ; 
 int /*<<< orphan*/  xenvif_set_skb_hash (struct xenvif*,struct sk_buff*) ; 

__attribute__((used)) static u16 xenvif_select_queue(struct net_device *dev, struct sk_buff *skb,
			       struct net_device *sb_dev)
{
	struct xenvif *vif = netdev_priv(dev);
	unsigned int size = vif->hash.size;
	unsigned int num_queues;

	/* If queues are not set up internally - always return 0
	 * as the packet going to be dropped anyway */
	num_queues = READ_ONCE(vif->num_queues);
	if (num_queues < 1)
		return 0;

	if (vif->hash.alg == XEN_NETIF_CTRL_HASH_ALGORITHM_NONE)
		return netdev_pick_tx(dev, skb, NULL) %
		       dev->real_num_tx_queues;

	xenvif_set_skb_hash(vif, skb);

	if (size == 0)
		return skb_get_hash_raw(skb) % dev->real_num_tx_queues;

	return vif->hash.mapping[vif->hash.mapping_sel]
				[skb_get_hash_raw(skb) % size];
}