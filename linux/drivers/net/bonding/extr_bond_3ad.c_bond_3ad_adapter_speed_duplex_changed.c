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
struct slave {int /*<<< orphan*/  dev; TYPE_1__* bond; } ;
struct port {int /*<<< orphan*/  actor_port_number; int /*<<< orphan*/  slave; } ;
struct TYPE_4__ {struct port port; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  mode_lock; } ;

/* Variables and functions */
 TYPE_2__* SLAVE_AD_INFO (struct slave*) ; 
 int /*<<< orphan*/  ad_update_actor_keys (struct port*,int) ; 
 int /*<<< orphan*/  slave_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slave_warn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void bond_3ad_adapter_speed_duplex_changed(struct slave *slave)
{
	struct port *port;

	port = &(SLAVE_AD_INFO(slave)->port);

	/* if slave is null, the whole port is not initialized */
	if (!port->slave) {
		slave_warn(slave->bond->dev, slave->dev,
			   "speed/duplex changed for uninitialized port\n");
		return;
	}

	spin_lock_bh(&slave->bond->mode_lock);
	ad_update_actor_keys(port, false);
	spin_unlock_bh(&slave->bond->mode_lock);
	slave_dbg(slave->bond->dev, slave->dev, "Port %d changed speed/duplex\n",
		  port->actor_port_number);
}