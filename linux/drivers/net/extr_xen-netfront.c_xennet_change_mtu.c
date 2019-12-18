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
struct net_device {int mtu; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETH_DATA_LEN ; 
 int XEN_NETIF_MAX_TX_SIZE ; 
 scalar_t__ xennet_can_sg (struct net_device*) ; 

__attribute__((used)) static int xennet_change_mtu(struct net_device *dev, int mtu)
{
	int max = xennet_can_sg(dev) ? XEN_NETIF_MAX_TX_SIZE : ETH_DATA_LEN;

	if (mtu > max)
		return -EINVAL;
	dev->mtu = mtu;
	return 0;
}