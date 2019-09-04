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
struct net_device {int dummy; } ;
struct mlxsw_sp_bridge_port {int /*<<< orphan*/  flags; } ;
struct mlxsw_sp_bridge {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  memcpy (unsigned long*,int /*<<< orphan*/ *,int) ; 
 struct mlxsw_sp_bridge_port* mlxsw_sp_bridge_port_find (struct mlxsw_sp_bridge*,struct net_device*) ; 

__attribute__((used)) static void mlxsw_sp_port_bridge_flags_get(struct mlxsw_sp_bridge *bridge,
					   struct net_device *dev,
					   unsigned long *brport_flags)
{
	struct mlxsw_sp_bridge_port *bridge_port;

	bridge_port = mlxsw_sp_bridge_port_find(bridge, dev);
	if (WARN_ON(!bridge_port))
		return;

	memcpy(brport_flags, &bridge_port->flags, sizeof(*brport_flags));
}