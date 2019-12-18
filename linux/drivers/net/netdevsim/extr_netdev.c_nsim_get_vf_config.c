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
struct nsim_bus_dev {int num_vfs; TYPE_1__* vfconfigs; } ;
struct netdevsim {struct nsim_bus_dev* nsim_bus_dev; } ;
struct net_device {int dummy; } ;
struct ifla_vf_info {int vf; int /*<<< orphan*/  rss_query_en; int /*<<< orphan*/  trusted; int /*<<< orphan*/  spoofchk; int /*<<< orphan*/  mac; int /*<<< orphan*/  qos; int /*<<< orphan*/  vlan_proto; int /*<<< orphan*/  vlan; int /*<<< orphan*/  max_tx_rate; int /*<<< orphan*/  min_tx_rate; int /*<<< orphan*/  linkstate; } ;
struct TYPE_2__ {int /*<<< orphan*/  rss_query_enabled; int /*<<< orphan*/  trusted; int /*<<< orphan*/  spoofchk_enabled; int /*<<< orphan*/  vf_mac; int /*<<< orphan*/  qos; int /*<<< orphan*/  vlan_proto; int /*<<< orphan*/  vlan; int /*<<< orphan*/  max_tx_rate; int /*<<< orphan*/  min_tx_rate; int /*<<< orphan*/  link_state; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct netdevsim* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
nsim_get_vf_config(struct net_device *dev, int vf, struct ifla_vf_info *ivi)
{
	struct netdevsim *ns = netdev_priv(dev);
	struct nsim_bus_dev *nsim_bus_dev = ns->nsim_bus_dev;

	if (vf >= nsim_bus_dev->num_vfs)
		return -EINVAL;

	ivi->vf = vf;
	ivi->linkstate = nsim_bus_dev->vfconfigs[vf].link_state;
	ivi->min_tx_rate = nsim_bus_dev->vfconfigs[vf].min_tx_rate;
	ivi->max_tx_rate = nsim_bus_dev->vfconfigs[vf].max_tx_rate;
	ivi->vlan = nsim_bus_dev->vfconfigs[vf].vlan;
	ivi->vlan_proto = nsim_bus_dev->vfconfigs[vf].vlan_proto;
	ivi->qos = nsim_bus_dev->vfconfigs[vf].qos;
	memcpy(&ivi->mac, nsim_bus_dev->vfconfigs[vf].vf_mac, ETH_ALEN);
	ivi->spoofchk = nsim_bus_dev->vfconfigs[vf].spoofchk_enabled;
	ivi->trusted = nsim_bus_dev->vfconfigs[vf].trusted;
	ivi->rss_query_en = nsim_bus_dev->vfconfigs[vf].rss_query_enabled;

	return 0;
}