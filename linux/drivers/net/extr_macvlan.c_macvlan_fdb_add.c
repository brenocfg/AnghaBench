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
typedef  int u16 ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct ndmsg {int dummy; } ;
struct macvlan_dev {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int NLM_F_REPLACE ; 
 int dev_mc_add_excl (struct net_device*,unsigned char const*) ; 
 int dev_uc_add_excl (struct net_device*,unsigned char const*) ; 
 scalar_t__ is_multicast_ether_addr (unsigned char const*) ; 
 scalar_t__ is_unicast_ether_addr (unsigned char const*) ; 
 int /*<<< orphan*/  macvlan_passthru (int /*<<< orphan*/ ) ; 
 struct macvlan_dev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int macvlan_fdb_add(struct ndmsg *ndm, struct nlattr *tb[],
			   struct net_device *dev,
			   const unsigned char *addr, u16 vid,
			   u16 flags,
			   struct netlink_ext_ack *extack)
{
	struct macvlan_dev *vlan = netdev_priv(dev);
	int err = -EINVAL;

	/* Support unicast filter only on passthru devices.
	 * Multicast filter should be allowed on all devices.
	 */
	if (!macvlan_passthru(vlan->port) && is_unicast_ether_addr(addr))
		return -EOPNOTSUPP;

	if (flags & NLM_F_REPLACE)
		return -EOPNOTSUPP;

	if (is_unicast_ether_addr(addr))
		err = dev_uc_add_excl(dev, addr);
	else if (is_multicast_ether_addr(addr))
		err = dev_mc_add_excl(dev, addr);

	return err;
}