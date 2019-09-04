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
struct ib_pd {int /*<<< orphan*/  usecnt; } ;
struct ib_mr {TYPE_1__* device; int /*<<< orphan*/  res; struct ib_dm* dm; struct ib_pd* pd; } ;
struct ib_dm {int /*<<< orphan*/  usecnt; } ;
struct TYPE_2__ {int (* dereg_mr ) (struct ib_mr*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_restrack_del (int /*<<< orphan*/ *) ; 
 int stub1 (struct ib_mr*) ; 

int ib_dereg_mr(struct ib_mr *mr)
{
	struct ib_pd *pd = mr->pd;
	struct ib_dm *dm = mr->dm;
	int ret;

	rdma_restrack_del(&mr->res);
	ret = mr->device->dereg_mr(mr);
	if (!ret) {
		atomic_dec(&pd->usecnt);
		if (dm)
			atomic_dec(&dm->usecnt);
	}

	return ret;
}