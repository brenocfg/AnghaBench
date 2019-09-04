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
struct skge_port {int /*<<< orphan*/  netdev; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 struct skge_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct skge_port const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  probe ; 

__attribute__((used)) static void skge_show_addr(struct net_device *dev)
{
	const struct skge_port *skge = netdev_priv(dev);

	netif_info(skge, probe, skge->netdev, "addr %pM\n", dev->dev_addr);
}