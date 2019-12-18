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
struct nfp_reprs {int /*<<< orphan*/ * reprs; } ;
struct nfp_app {TYPE_1__* pf; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct net_device* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct net_device *
nfp_repr_get_locked(struct nfp_app *app, struct nfp_reprs *set, unsigned int id)
{
	return rcu_dereference_protected(set->reprs[id],
					 lockdep_is_held(&app->pf->lock));
}