#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct nsim_bus_dev {int num_vfs; TYPE_1__* vfconfigs; } ;
struct netdevsim {struct nsim_bus_dev* nsim_bus_dev; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vf_mac; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct netdevsim* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int nsim_set_vf_mac(struct net_device *dev, int vf, u8 *mac)
{
	struct netdevsim *ns = netdev_priv(dev);
	struct nsim_bus_dev *nsim_bus_dev = ns->nsim_bus_dev;

	/* Only refuse multicast addresses, zero address can mean unset/any. */
	if (vf >= nsim_bus_dev->num_vfs || is_multicast_ether_addr(mac))
		return -EINVAL;
	memcpy(nsim_bus_dev->vfconfigs[vf].vf_mac, mac, ETH_ALEN);

	return 0;
}