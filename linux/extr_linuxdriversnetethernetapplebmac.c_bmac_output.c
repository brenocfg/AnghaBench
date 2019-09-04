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
struct bmac_data {int /*<<< orphan*/  queue; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  bmac_start (struct net_device*) ; 
 struct bmac_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static netdev_tx_t
bmac_output(struct sk_buff *skb, struct net_device *dev)
{
	struct bmac_data *bp = netdev_priv(dev);
	skb_queue_tail(bp->queue, skb);
	bmac_start(dev);
	return NETDEV_TX_OK;
}