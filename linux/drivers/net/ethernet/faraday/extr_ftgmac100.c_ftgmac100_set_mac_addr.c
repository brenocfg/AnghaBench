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
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  eth_commit_mac_addr_change (struct net_device*,void*) ; 
 int eth_prepare_mac_addr_change (struct net_device*,void*) ; 
 int /*<<< orphan*/  ftgmac100_write_mac_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ftgmac100_set_mac_addr(struct net_device *dev, void *p)
{
	int ret;

	ret = eth_prepare_mac_addr_change(dev, p);
	if (ret < 0)
		return ret;

	eth_commit_mac_addr_change(dev, p);
	ftgmac100_write_mac_addr(netdev_priv(dev), dev->dev_addr);

	return 0;
}