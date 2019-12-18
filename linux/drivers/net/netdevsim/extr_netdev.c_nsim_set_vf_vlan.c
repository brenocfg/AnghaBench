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
typedef  int u8 ;
typedef  int u16 ;
struct nsim_bus_dev {int num_vfs; TYPE_1__* vfconfigs; } ;
struct netdevsim {struct nsim_bus_dev* nsim_bus_dev; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int vlan; int qos; int /*<<< orphan*/  vlan_proto; } ;

/* Variables and functions */
 int EINVAL ; 
 struct netdevsim* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int nsim_set_vf_vlan(struct net_device *dev, int vf,
			    u16 vlan, u8 qos, __be16 vlan_proto)
{
	struct netdevsim *ns = netdev_priv(dev);
	struct nsim_bus_dev *nsim_bus_dev = ns->nsim_bus_dev;

	if (vf >= nsim_bus_dev->num_vfs || vlan > 4095 || qos > 7)
		return -EINVAL;

	nsim_bus_dev->vfconfigs[vf].vlan = vlan;
	nsim_bus_dev->vfconfigs[vf].qos = qos;
	nsim_bus_dev->vfconfigs[vf].vlan_proto = vlan_proto;

	return 0;
}