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
struct pxa168_eth_private {int dummy; } ;
struct net_device {int mtu; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct pxa168_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 scalar_t__ pxa168_eth_open (struct net_device*) ; 
 int /*<<< orphan*/  pxa168_eth_stop (struct net_device*) ; 
 int set_port_config_ext (struct pxa168_eth_private*) ; 

__attribute__((used)) static int pxa168_eth_change_mtu(struct net_device *dev, int mtu)
{
	int retval;
	struct pxa168_eth_private *pep = netdev_priv(dev);

	dev->mtu = mtu;
	retval = set_port_config_ext(pep);

	if (!netif_running(dev))
		return 0;

	/*
	 * Stop and then re-open the interface. This will allocate RX
	 * skbs of the new MTU.
	 * There is a possible danger that the open will not succeed,
	 * due to memory being full.
	 */
	pxa168_eth_stop(dev);
	if (pxa168_eth_open(dev)) {
		dev_err(&dev->dev,
			"fatal error on re-opening device after MTU change\n");
	}

	return 0;
}