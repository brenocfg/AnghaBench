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
struct sky2_port {int dummy; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 struct sky2_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct sky2_port const*,int /*<<< orphan*/ ,struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  probe ; 

__attribute__((used)) static void sky2_show_addr(struct net_device *dev)
{
	const struct sky2_port *sky2 = netdev_priv(dev);

	netif_info(sky2, probe, dev, "addr %pM\n", dev->dev_addr);
}