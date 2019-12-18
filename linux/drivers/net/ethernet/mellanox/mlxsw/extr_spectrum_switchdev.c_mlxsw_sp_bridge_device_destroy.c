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
struct mlxsw_sp_bridge_device {int /*<<< orphan*/  mids_list; int /*<<< orphan*/  ports_list; scalar_t__ vlan_enabled; int /*<<< orphan*/  list; int /*<<< orphan*/  dev; } ;
struct mlxsw_sp_bridge {int vlan_enabled_exists; int /*<<< orphan*/  mlxsw_sp; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_bridge_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_bridge_device_rifs_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlxsw_sp_bridge_device_destroy(struct mlxsw_sp_bridge *bridge,
			       struct mlxsw_sp_bridge_device *bridge_device)
{
	mlxsw_sp_bridge_device_rifs_destroy(bridge->mlxsw_sp,
					    bridge_device->dev);
	list_del(&bridge_device->list);
	if (bridge_device->vlan_enabled)
		bridge->vlan_enabled_exists = false;
	WARN_ON(!list_empty(&bridge_device->ports_list));
	WARN_ON(!list_empty(&bridge_device->mids_list));
	kfree(bridge_device);
}