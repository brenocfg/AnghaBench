#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct mlxsw_sp_bridge_device {int vlan_enabled; int /*<<< orphan*/  list; int /*<<< orphan*/  mids_list; int /*<<< orphan*/  ops; int /*<<< orphan*/  ports_list; int /*<<< orphan*/  mrouter; int /*<<< orphan*/  multicast_enabled; struct net_device* dev; } ;
struct mlxsw_sp_bridge {int vlan_enabled_exists; int /*<<< orphan*/  bridges_list; int /*<<< orphan*/  bridge_8021d_ops; int /*<<< orphan*/  bridge_8021q_ops; TYPE_2__* mlxsw_sp; } ;
struct device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* bus_info; } ;
struct TYPE_3__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct mlxsw_sp_bridge_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_multicast_enabled (struct net_device*) ; 
 int /*<<< orphan*/  br_multicast_router (struct net_device*) ; 
 int br_vlan_enabled (struct net_device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct mlxsw_sp_bridge_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mlxsw_sp_bridge_device *
mlxsw_sp_bridge_device_create(struct mlxsw_sp_bridge *bridge,
			      struct net_device *br_dev)
{
	struct device *dev = bridge->mlxsw_sp->bus_info->dev;
	struct mlxsw_sp_bridge_device *bridge_device;
	bool vlan_enabled = br_vlan_enabled(br_dev);

	if (vlan_enabled && bridge->vlan_enabled_exists) {
		dev_err(dev, "Only one VLAN-aware bridge is supported\n");
		return ERR_PTR(-EINVAL);
	}

	bridge_device = kzalloc(sizeof(*bridge_device), GFP_KERNEL);
	if (!bridge_device)
		return ERR_PTR(-ENOMEM);

	bridge_device->dev = br_dev;
	bridge_device->vlan_enabled = vlan_enabled;
	bridge_device->multicast_enabled = br_multicast_enabled(br_dev);
	bridge_device->mrouter = br_multicast_router(br_dev);
	INIT_LIST_HEAD(&bridge_device->ports_list);
	if (vlan_enabled) {
		bridge->vlan_enabled_exists = true;
		bridge_device->ops = bridge->bridge_8021q_ops;
	} else {
		bridge_device->ops = bridge->bridge_8021d_ops;
	}
	INIT_LIST_HEAD(&bridge_device->mids_list);
	list_add(&bridge_device->list, &bridge->bridges_list);

	return bridge_device;
}