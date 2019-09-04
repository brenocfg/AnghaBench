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
struct mlxsw_sp_bridge_port {int /*<<< orphan*/  vlans_list; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_bridge_port*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlxsw_sp_bridge_port_destroy(struct mlxsw_sp_bridge_port *bridge_port)
{
	list_del(&bridge_port->list);
	WARN_ON(!list_empty(&bridge_port->vlans_list));
	kfree(bridge_port);
}