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
struct ib_sig_attrs {int dummy; } ;
struct ib_pd {int /*<<< orphan*/  usecnt; } ;
struct ib_mr {TYPE_2__* device; int /*<<< orphan*/  res; struct ib_sig_attrs* sig_attrs; struct ib_dm* dm; struct ib_pd* pd; } ;
struct ib_dm {int /*<<< orphan*/  usecnt; } ;
struct TYPE_3__ {int (* dereg_mr ) (struct ib_mr*,struct ib_udata*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ib_sig_attrs*) ; 
 int /*<<< orphan*/  rdma_restrack_del (int /*<<< orphan*/ *) ; 
 int stub1 (struct ib_mr*,struct ib_udata*) ; 

int ib_dereg_mr_user(struct ib_mr *mr, struct ib_udata *udata)
{
	struct ib_pd *pd = mr->pd;
	struct ib_dm *dm = mr->dm;
	struct ib_sig_attrs *sig_attrs = mr->sig_attrs;
	int ret;

	rdma_restrack_del(&mr->res);
	ret = mr->device->ops.dereg_mr(mr, udata);
	if (!ret) {
		atomic_dec(&pd->usecnt);
		if (dm)
			atomic_dec(&dm->usecnt);
		kfree(sig_attrs);
	}

	return ret;
}