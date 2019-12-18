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
typedef  int /*<<< orphan*/  u16 ;
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;
struct ndmsg {int dummy; } ;
struct macvlan_dev {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int dev_mc_del (struct net_device*,unsigned char const*) ; 
 int dev_uc_del (struct net_device*,unsigned char const*) ; 
 scalar_t__ is_multicast_ether_addr (unsigned char const*) ; 
 scalar_t__ is_unicast_ether_addr (unsigned char const*) ; 
 int /*<<< orphan*/  macvlan_passthru (int /*<<< orphan*/ ) ; 
 struct macvlan_dev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int macvlan_fdb_del(struct ndmsg *ndm, struct nlattr *tb[],
			   struct net_device *dev,
			   const unsigned char *addr, u16 vid)
{
	struct macvlan_dev *vlan = netdev_priv(dev);
	int err = -EINVAL;

	/* Support unicast filter only on passthru devices.
	 * Multicast filter should be allowed on all devices.
	 */
	if (!macvlan_passthru(vlan->port) && is_unicast_ether_addr(addr))
		return -EOPNOTSUPP;

	if (is_unicast_ether_addr(addr))
		err = dev_uc_del(dev, addr);
	else if (is_multicast_ether_addr(addr))
		err = dev_mc_del(dev, addr);

	return err;
}