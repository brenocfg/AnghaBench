#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct slave {TYPE_1__* dev; TYPE_2__* bond; } ;
struct port {int /*<<< orphan*/  actor_port_number; int /*<<< orphan*/  slave; } ;
struct TYPE_6__ {struct port port; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  mode_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_3__* SLAVE_AD_INFO (struct slave*) ; 
 int /*<<< orphan*/  ad_update_actor_keys (struct port*,int) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void bond_3ad_adapter_speed_duplex_changed(struct slave *slave)
{
	struct port *port;

	port = &(SLAVE_AD_INFO(slave)->port);

	/* if slave is null, the whole port is not initialized */
	if (!port->slave) {
		netdev_warn(slave->bond->dev,
			    "speed/duplex changed for uninitialized port %s\n",
			    slave->dev->name);
		return;
	}

	spin_lock_bh(&slave->bond->mode_lock);
	ad_update_actor_keys(port, false);
	spin_unlock_bh(&slave->bond->mode_lock);
	netdev_dbg(slave->bond->dev, "Port %d slave %s changed speed/duplex\n",
		   port->actor_port_number, slave->dev->name);
}