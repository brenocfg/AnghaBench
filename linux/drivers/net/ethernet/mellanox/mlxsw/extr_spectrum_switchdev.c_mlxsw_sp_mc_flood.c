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
struct mlxsw_sp_bridge_port {int mrouter; int flags; struct mlxsw_sp_bridge_device* bridge_device; } ;
struct mlxsw_sp_bridge_device {scalar_t__ multicast_enabled; } ;

/* Variables and functions */
 int BR_MCAST_FLOOD ; 

__attribute__((used)) static bool mlxsw_sp_mc_flood(const struct mlxsw_sp_bridge_port *bridge_port)
{
	const struct mlxsw_sp_bridge_device *bridge_device;

	bridge_device = bridge_port->bridge_device;
	return bridge_device->multicast_enabled ? bridge_port->mrouter :
					bridge_port->flags & BR_MCAST_FLOOD;
}