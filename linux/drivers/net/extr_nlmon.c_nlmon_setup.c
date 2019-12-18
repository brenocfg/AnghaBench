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
struct nlmsghdr {int dummy; } ;
struct net_device {int needs_free_netdev; int features; int min_mtu; int /*<<< orphan*/  mtu; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_NETLINK ; 
 int /*<<< orphan*/  IFF_NOARP ; 
 int /*<<< orphan*/  IFF_NO_QUEUE ; 
 int NETIF_F_FRAGLIST ; 
 int NETIF_F_HIGHDMA ; 
 int NETIF_F_LLTX ; 
 int NETIF_F_SG ; 
 int /*<<< orphan*/  NLMSG_GOODSIZE ; 
 int /*<<< orphan*/  nlmon_ethtool_ops ; 
 int /*<<< orphan*/  nlmon_ops ; 

__attribute__((used)) static void nlmon_setup(struct net_device *dev)
{
	dev->type = ARPHRD_NETLINK;
	dev->priv_flags |= IFF_NO_QUEUE;

	dev->netdev_ops	= &nlmon_ops;
	dev->ethtool_ops = &nlmon_ethtool_ops;
	dev->needs_free_netdev = true;

	dev->features = NETIF_F_SG | NETIF_F_FRAGLIST |
			NETIF_F_HIGHDMA | NETIF_F_LLTX;
	dev->flags = IFF_NOARP;

	/* That's rather a softlimit here, which, of course,
	 * can be altered. Not a real MTU, but what is to be
	 * expected in most cases.
	 */
	dev->mtu = NLMSG_GOODSIZE;
	dev->min_mtu = sizeof(struct nlmsghdr);
}