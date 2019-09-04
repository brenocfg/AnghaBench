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
struct pch_gbe_adapter {int /*<<< orphan*/  mii; } ;
struct net_device {int dummy; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
 int SIOCSHWTSTAMP ; 
 int generic_mii_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int hwtstamp_ioctl (struct net_device*,struct ifreq*,int) ; 
 int /*<<< orphan*/  if_mii (struct ifreq*) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int) ; 
 struct pch_gbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int pch_gbe_ioctl(struct net_device *netdev, struct ifreq *ifr, int cmd)
{
	struct pch_gbe_adapter *adapter = netdev_priv(netdev);

	netdev_dbg(netdev, "cmd : 0x%04x\n", cmd);

	if (cmd == SIOCSHWTSTAMP)
		return hwtstamp_ioctl(netdev, ifr, cmd);

	return generic_mii_ioctl(&adapter->mii, if_mii(ifr), cmd, NULL);
}