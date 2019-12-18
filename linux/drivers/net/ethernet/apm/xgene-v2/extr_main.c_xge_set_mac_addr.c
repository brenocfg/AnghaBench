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
struct xge_pdata {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int eth_mac_addr (struct net_device*,void*) ; 
 struct xge_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  xge_mac_set_station_addr (struct xge_pdata*) ; 

__attribute__((used)) static int xge_set_mac_addr(struct net_device *ndev, void *addr)
{
	struct xge_pdata *pdata = netdev_priv(ndev);
	int ret;

	ret = eth_mac_addr(ndev, addr);
	if (ret)
		return ret;

	xge_mac_set_station_addr(pdata);

	return 0;
}