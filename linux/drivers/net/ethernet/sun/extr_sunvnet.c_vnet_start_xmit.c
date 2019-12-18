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
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  sunvnet_start_xmit_common (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnet_tx_port_find ; 

__attribute__((used)) static netdev_tx_t vnet_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	return sunvnet_start_xmit_common(skb, dev, vnet_tx_port_find);
}