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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct mvneta_port {int rxq_def; } ;

/* Variables and functions */
 int /*<<< orphan*/  eth_commit_mac_addr_change (struct net_device*,void*) ; 
 int eth_prepare_mac_addr_change (struct net_device*,void*) ; 
 int /*<<< orphan*/  mvneta_mac_addr_set (struct mvneta_port*,int /*<<< orphan*/ ,int) ; 
 struct mvneta_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mvneta_set_mac_addr(struct net_device *dev, void *addr)
{
	struct mvneta_port *pp = netdev_priv(dev);
	struct sockaddr *sockaddr = addr;
	int ret;

	ret = eth_prepare_mac_addr_change(dev, addr);
	if (ret < 0)
		return ret;
	/* Remove previous address table entry */
	mvneta_mac_addr_set(pp, dev->dev_addr, -1);

	/* Set new addr in hw */
	mvneta_mac_addr_set(pp, sockaddr->sa_data, pp->rxq_def);

	eth_commit_mac_addr_change(dev, addr);
	return 0;
}