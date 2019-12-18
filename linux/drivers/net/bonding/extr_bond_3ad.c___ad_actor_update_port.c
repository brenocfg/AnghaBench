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
struct port {int /*<<< orphan*/  actor_system_priority; int /*<<< orphan*/  actor_system; int /*<<< orphan*/  slave; } ;
struct bonding {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  sys_priority; int /*<<< orphan*/  sys_mac_addr; } ;
struct TYPE_4__ {TYPE_1__ system; } ;

/* Variables and functions */
 TYPE_2__ BOND_AD_INFO (struct bonding const*) ; 
 struct bonding* bond_get_bond_by_slave (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __ad_actor_update_port(struct port *port)
{
	const struct bonding *bond = bond_get_bond_by_slave(port->slave);

	port->actor_system = BOND_AD_INFO(bond).system.sys_mac_addr;
	port->actor_system_priority = BOND_AD_INFO(bond).system.sys_priority;
}