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
struct mlxsw_sp_bridge_device {int /*<<< orphan*/  ports_list; } ;
struct mlxsw_sp_bridge {int dummy; } ;

/* Variables and functions */
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_bridge_device_destroy (struct mlxsw_sp_bridge*,struct mlxsw_sp_bridge_device*) ; 

__attribute__((used)) static void
mlxsw_sp_bridge_device_put(struct mlxsw_sp_bridge *bridge,
			   struct mlxsw_sp_bridge_device *bridge_device)
{
	if (list_empty(&bridge_device->ports_list))
		mlxsw_sp_bridge_device_destroy(bridge, bridge_device);
}