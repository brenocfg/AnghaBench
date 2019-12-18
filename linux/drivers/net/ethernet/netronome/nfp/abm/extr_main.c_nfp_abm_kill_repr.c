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
struct nfp_reprs {int /*<<< orphan*/ * reprs; } ;
struct nfp_repr {int dummy; } ;
struct nfp_app {int dummy; } ;
struct nfp_abm_link {size_t id; } ;
struct net_device {int dummy; } ;
typedef  enum nfp_repr_type { ____Placeholder_nfp_repr_type } nfp_repr_type ;

/* Variables and functions */
 scalar_t__ netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nfp_repr_clean_and_free (struct nfp_repr*) ; 
 struct net_device* nfp_repr_get_locked (struct nfp_app*,struct nfp_reprs*,size_t) ; 
 struct nfp_reprs* nfp_reprs_get_locked (struct nfp_app*,int) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static void
nfp_abm_kill_repr(struct nfp_app *app, struct nfp_abm_link *alink,
		  enum nfp_repr_type rtype)
{
	struct net_device *netdev;
	struct nfp_reprs *reprs;

	reprs = nfp_reprs_get_locked(app, rtype);
	netdev = nfp_repr_get_locked(app, reprs, alink->id);
	if (!netdev)
		return;
	rtnl_lock();
	rcu_assign_pointer(reprs->reprs[alink->id], NULL);
	rtnl_unlock();
	synchronize_rcu();
	/* Cast to make sure nfp_repr_clean_and_free() takes a nfp_repr */
	nfp_repr_clean_and_free((struct nfp_repr *)netdev_priv(netdev));
}