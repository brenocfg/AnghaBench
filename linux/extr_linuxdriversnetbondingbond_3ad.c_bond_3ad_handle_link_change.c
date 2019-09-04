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
struct slave {TYPE_2__* bond; TYPE_1__* dev; } ;
struct port {int is_enabled; int /*<<< orphan*/  actor_port_number; int /*<<< orphan*/  slave; } ;
struct aggregator {int dummy; } ;
struct TYPE_6__ {struct port port; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  mode_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 char BOND_LINK_UP ; 
 TYPE_3__* SLAVE_AD_INFO (struct slave*) ; 
 struct aggregator* __get_first_agg (struct port*) ; 
 int /*<<< orphan*/  ad_agg_selection_logic (struct aggregator*,int*) ; 
 int /*<<< orphan*/  ad_update_actor_keys (struct port*,int) ; 
 int /*<<< orphan*/  bond_update_slave_arr (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void bond_3ad_handle_link_change(struct slave *slave, char link)
{
	struct aggregator *agg;
	struct port *port;
	bool dummy;

	port = &(SLAVE_AD_INFO(slave)->port);

	/* if slave is null, the whole port is not initialized */
	if (!port->slave) {
		netdev_warn(slave->bond->dev, "link status changed for uninitialized port on %s\n",
			    slave->dev->name);
		return;
	}

	spin_lock_bh(&slave->bond->mode_lock);
	/* on link down we are zeroing duplex and speed since
	 * some of the adaptors(ce1000.lan) report full duplex/speed
	 * instead of N/A(duplex) / 0(speed).
	 *
	 * on link up we are forcing recheck on the duplex and speed since
	 * some of he adaptors(ce1000.lan) report.
	 */
	if (link == BOND_LINK_UP) {
		port->is_enabled = true;
		ad_update_actor_keys(port, false);
	} else {
		/* link has failed */
		port->is_enabled = false;
		ad_update_actor_keys(port, true);
	}
	agg = __get_first_agg(port);
	ad_agg_selection_logic(agg, &dummy);

	spin_unlock_bh(&slave->bond->mode_lock);

	netdev_dbg(slave->bond->dev, "Port %d changed link status to %s\n",
		   port->actor_port_number,
		   link == BOND_LINK_UP ? "UP" : "DOWN");

	/* RTNL is held and mode_lock is released so it's safe
	 * to update slave_array here.
	 */
	bond_update_slave_arr(slave->bond, NULL);
}