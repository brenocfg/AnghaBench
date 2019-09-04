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
struct nfp_reprs {int dummy; } ;
struct nfp_app {TYPE_1__* pf; int /*<<< orphan*/ * reprs; } ;
typedef  enum nfp_repr_type { ____Placeholder_nfp_repr_type } nfp_repr_type ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct nfp_reprs* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct nfp_reprs *
nfp_reprs_get_locked(struct nfp_app *app, enum nfp_repr_type type)
{
	return rcu_dereference_protected(app->reprs[type],
					 lockdep_is_held(&app->pf->lock));
}