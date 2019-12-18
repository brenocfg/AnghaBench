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
struct ib_udata {int dummy; } ;
struct ib_pd {TYPE_2__* device; int /*<<< orphan*/  res; int /*<<< orphan*/  usecnt; int /*<<< orphan*/ * __internal_mr; } ;
struct TYPE_3__ {int (* dereg_mr ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* dealloc_pd ) (struct ib_pd*,struct ib_udata*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ib_pd*) ; 
 int /*<<< orphan*/  rdma_restrack_del (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct ib_pd*,struct ib_udata*) ; 

void ib_dealloc_pd_user(struct ib_pd *pd, struct ib_udata *udata)
{
	int ret;

	if (pd->__internal_mr) {
		ret = pd->device->ops.dereg_mr(pd->__internal_mr, NULL);
		WARN_ON(ret);
		pd->__internal_mr = NULL;
	}

	/* uverbs manipulates usecnt with proper locking, while the kabi
	   requires the caller to guarantee we can't race here. */
	WARN_ON(atomic_read(&pd->usecnt));

	rdma_restrack_del(&pd->res);
	pd->device->ops.dealloc_pd(pd, udata);
	kfree(pd);
}