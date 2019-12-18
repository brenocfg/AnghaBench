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
struct bgmac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bgmac_write_mac_address (struct bgmac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_commit_mac_addr_change (struct net_device*,void*) ; 
 int eth_prepare_mac_addr_change (struct net_device*,void*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bgmac* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bgmac_set_mac_address(struct net_device *net_dev, void *addr)
{
	struct bgmac *bgmac = netdev_priv(net_dev);
	struct sockaddr *sa = addr;
	int ret;

	ret = eth_prepare_mac_addr_change(net_dev, addr);
	if (ret < 0)
		return ret;

	ether_addr_copy(net_dev->dev_addr, sa->sa_data);
	bgmac_write_mac_address(bgmac, net_dev->dev_addr);

	eth_commit_mac_addr_change(net_dev, addr);
	return 0;
}