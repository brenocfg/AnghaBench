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
struct nfp_reprs {int num_reprs; int /*<<< orphan*/ * reprs; } ;
struct nfp_repr {TYPE_1__* port; } ;
struct nfp_app {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ NFP_PORT_INVALID ; 
 int /*<<< orphan*/  NFP_REPR_TYPE_PHYS_PORT ; 
 struct nfp_repr* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nfp_app_repr_preclean (struct nfp_app*,struct net_device*) ; 
 int /*<<< orphan*/  nfp_repr_clean (struct nfp_repr*) ; 
 struct net_device* nfp_repr_get_locked (struct nfp_app*,struct nfp_reprs*,int) ; 
 struct nfp_reprs* nfp_reprs_get_locked (struct nfp_app*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

int nfp_reprs_resync_phys_ports(struct nfp_app *app)
{
	struct net_device *netdev;
	struct nfp_reprs *reprs;
	struct nfp_repr *repr;
	int i;

	reprs = nfp_reprs_get_locked(app, NFP_REPR_TYPE_PHYS_PORT);
	if (!reprs)
		return 0;

	for (i = 0; i < reprs->num_reprs; i++) {
		netdev = nfp_repr_get_locked(app, reprs, i);
		if (!netdev)
			continue;

		repr = netdev_priv(netdev);
		if (repr->port->type != NFP_PORT_INVALID)
			continue;

		nfp_app_repr_preclean(app, netdev);
		rtnl_lock();
		rcu_assign_pointer(reprs->reprs[i], NULL);
		rtnl_unlock();
		synchronize_rcu();
		nfp_repr_clean(repr);
	}

	return 0;
}