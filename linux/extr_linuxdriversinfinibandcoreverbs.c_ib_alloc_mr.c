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
typedef  int /*<<< orphan*/  u32 ;
struct ib_pd {int /*<<< orphan*/  usecnt; TYPE_1__* device; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct ib_mr {int need_inval; TYPE_2__ res; int /*<<< orphan*/ * uobject; int /*<<< orphan*/ * dm; struct ib_pd* pd; TYPE_1__* device; } ;
typedef  enum ib_mr_type { ____Placeholder_ib_mr_type } ib_mr_type ;
struct TYPE_3__ {struct ib_mr* (* alloc_mr ) (struct ib_pd*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EOPNOTSUPP ; 
 struct ib_mr* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct ib_mr*) ; 
 int /*<<< orphan*/  RDMA_RESTRACK_MR ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_restrack_add (TYPE_2__*) ; 
 struct ib_mr* stub1 (struct ib_pd*,int,int /*<<< orphan*/ ) ; 

struct ib_mr *ib_alloc_mr(struct ib_pd *pd,
			  enum ib_mr_type mr_type,
			  u32 max_num_sg)
{
	struct ib_mr *mr;

	if (!pd->device->alloc_mr)
		return ERR_PTR(-EOPNOTSUPP);

	mr = pd->device->alloc_mr(pd, mr_type, max_num_sg);
	if (!IS_ERR(mr)) {
		mr->device  = pd->device;
		mr->pd      = pd;
		mr->dm      = NULL;
		mr->uobject = NULL;
		atomic_inc(&pd->usecnt);
		mr->need_inval = false;
		mr->res.type = RDMA_RESTRACK_MR;
		rdma_restrack_add(&mr->res);
	}

	return mr;
}