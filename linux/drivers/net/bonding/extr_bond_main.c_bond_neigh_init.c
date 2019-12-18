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
struct slave {TYPE_2__* dev; } ;
struct net_device_ops {int (* ndo_neigh_setup ) (TYPE_2__*,struct neigh_parms*) ;} ;
struct neighbour {TYPE_1__* parms; int /*<<< orphan*/  dev; } ;
struct neigh_parms {int (* neigh_setup ) (struct neighbour*) ;int /*<<< orphan*/ * neigh_cleanup; } ;
struct bonding {int dummy; } ;
struct TYPE_4__ {struct net_device_ops* netdev_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/ * neigh_cleanup; } ;

/* Variables and functions */
 struct slave* bond_first_slave (struct bonding*) ; 
 struct bonding* netdev_priv (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,struct neigh_parms*) ; 
 int stub2 (struct neighbour*) ; 

__attribute__((used)) static int bond_neigh_init(struct neighbour *n)
{
	struct bonding *bond = netdev_priv(n->dev);
	const struct net_device_ops *slave_ops;
	struct neigh_parms parms;
	struct slave *slave;
	int ret;

	slave = bond_first_slave(bond);
	if (!slave)
		return 0;
	slave_ops = slave->dev->netdev_ops;
	if (!slave_ops->ndo_neigh_setup)
		return 0;

	parms.neigh_setup = NULL;
	parms.neigh_cleanup = NULL;
	ret = slave_ops->ndo_neigh_setup(slave->dev, &parms);
	if (ret)
		return ret;

	/* Assign slave's neigh_cleanup to neighbour in case cleanup is called
	 * after the last slave has been detached.  Assumes that all slaves
	 * utilize the same neigh_cleanup (true at this writing as only user
	 * is ipoib).
	 */
	n->parms->neigh_cleanup = parms.neigh_cleanup;

	if (!parms.neigh_setup)
		return 0;

	return parms.neigh_setup(n);
}