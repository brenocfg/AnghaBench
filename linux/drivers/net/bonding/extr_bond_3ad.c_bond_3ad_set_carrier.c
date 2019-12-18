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
struct slave {int dummy; } ;
struct TYPE_3__ {scalar_t__ min_links; } ;
struct bonding {int /*<<< orphan*/  dev; TYPE_1__ params; } ;
struct aggregator {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  aggregator; } ;

/* Variables and functions */
 TYPE_2__* SLAVE_AD_INFO (struct slave*) ; 
 scalar_t__ __agg_active_ports (struct aggregator*) ; 
 struct aggregator* __get_active_agg (int /*<<< orphan*/ *) ; 
 struct slave* bond_first_slave_rcu (struct bonding*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int bond_3ad_set_carrier(struct bonding *bond)
{
	struct aggregator *active;
	struct slave *first_slave;
	int ret = 1;

	rcu_read_lock();
	first_slave = bond_first_slave_rcu(bond);
	if (!first_slave) {
		ret = 0;
		goto out;
	}
	active = __get_active_agg(&(SLAVE_AD_INFO(first_slave)->aggregator));
	if (active) {
		/* are enough slaves available to consider link up? */
		if (__agg_active_ports(active) < bond->params.min_links) {
			if (netif_carrier_ok(bond->dev)) {
				netif_carrier_off(bond->dev);
				goto out;
			}
		} else if (!netif_carrier_ok(bond->dev)) {
			netif_carrier_on(bond->dev);
			goto out;
		}
	} else if (netif_carrier_ok(bond->dev)) {
		netif_carrier_off(bond->dev);
	}
out:
	rcu_read_unlock();
	return ret;
}