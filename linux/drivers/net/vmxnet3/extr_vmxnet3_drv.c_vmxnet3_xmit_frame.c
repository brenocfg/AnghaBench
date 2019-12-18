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
struct vmxnet3_adapter {size_t num_tx_queues; int /*<<< orphan*/ * tx_queue; } ;
struct sk_buff {size_t queue_mapping; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct vmxnet3_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  vmxnet3_tq_xmit (struct sk_buff*,int /*<<< orphan*/ *,struct vmxnet3_adapter*,struct net_device*) ; 

__attribute__((used)) static netdev_tx_t
vmxnet3_xmit_frame(struct sk_buff *skb, struct net_device *netdev)
{
	struct vmxnet3_adapter *adapter = netdev_priv(netdev);

	BUG_ON(skb->queue_mapping > adapter->num_tx_queues);
	return vmxnet3_tq_xmit(skb,
			       &adapter->tx_queue[skb->queue_mapping],
			       adapter, netdev);
}