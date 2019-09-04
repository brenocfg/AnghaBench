#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct slave {int dummy; } ;
struct port {int dummy; } ;
struct bonding {int dummy; } ;
struct aggregator {int dummy; } ;
struct TYPE_2__ {struct aggregator aggregator; } ;

/* Variables and functions */
 TYPE_1__* SLAVE_AD_INFO (struct slave*) ; 
 struct bonding* __get_bond_by_port (struct port*) ; 
 struct slave* bond_first_slave_rcu (struct bonding*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static inline struct aggregator *__get_first_agg(struct port *port)
{
	struct bonding *bond = __get_bond_by_port(port);
	struct slave *first_slave;
	struct aggregator *agg;

	/* If there's no bond for this port, or bond has no slaves */
	if (bond == NULL)
		return NULL;

	rcu_read_lock();
	first_slave = bond_first_slave_rcu(bond);
	agg = first_slave ? &(SLAVE_AD_INFO(first_slave)->aggregator) : NULL;
	rcu_read_unlock();

	return agg;
}