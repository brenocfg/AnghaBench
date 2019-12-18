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
struct nfp_reprs {int num_reprs; } ;
struct nfp_app {TYPE_1__* pf; int /*<<< orphan*/ * reprs; } ;
struct net_device {int dummy; } ;
typedef  enum nfp_repr_type { ____Placeholder_nfp_repr_type } nfp_repr_type ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_app_repr_preclean (struct nfp_app*,struct net_device*) ; 
 struct nfp_reprs* nfp_app_reprs_set (struct nfp_app*,int,int /*<<< orphan*/ *) ; 
 struct net_device* nfp_repr_get_locked (struct nfp_app*,struct nfp_reprs*,int) ; 
 int /*<<< orphan*/  nfp_reprs_clean_and_free (struct nfp_app*,struct nfp_reprs*) ; 
 struct nfp_reprs* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void
nfp_reprs_clean_and_free_by_type(struct nfp_app *app, enum nfp_repr_type type)
{
	struct net_device *netdev;
	struct nfp_reprs *reprs;
	int i;

	reprs = rcu_dereference_protected(app->reprs[type],
					  lockdep_is_held(&app->pf->lock));
	if (!reprs)
		return;

	/* Preclean must happen before we remove the reprs reference from the
	 * app below.
	 */
	for (i = 0; i < reprs->num_reprs; i++) {
		netdev = nfp_repr_get_locked(app, reprs, i);
		if (netdev)
			nfp_app_repr_preclean(app, netdev);
	}

	reprs = nfp_app_reprs_set(app, type, NULL);

	synchronize_rcu();
	nfp_reprs_clean_and_free(app, reprs);
}