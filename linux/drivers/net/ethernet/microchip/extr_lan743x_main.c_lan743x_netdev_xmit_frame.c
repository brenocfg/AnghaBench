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
struct net_device {int dummy; } ;
struct lan743x_adapter {int /*<<< orphan*/ * tx; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  lan743x_tx_xmit_frame (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct lan743x_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static netdev_tx_t lan743x_netdev_xmit_frame(struct sk_buff *skb,
					     struct net_device *netdev)
{
	struct lan743x_adapter *adapter = netdev_priv(netdev);

	return lan743x_tx_xmit_frame(&adapter->tx[0], skb);
}