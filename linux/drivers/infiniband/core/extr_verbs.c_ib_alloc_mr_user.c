#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ib_udata {int dummy; } ;
struct ib_pd {int /*<<< orphan*/  usecnt; TYPE_2__* device; } ;
struct TYPE_6__ {int /*<<< orphan*/  type; } ;
struct ib_mr {int need_inval; int type; int /*<<< orphan*/ * sig_attrs; TYPE_3__ res; int /*<<< orphan*/ * uobject; int /*<<< orphan*/ * dm; struct ib_pd* pd; TYPE_2__* device; } ;
typedef  enum ib_mr_type { ____Placeholder_ib_mr_type } ib_mr_type ;
struct TYPE_4__ {struct ib_mr* (* alloc_mr ) (struct ib_pd*,int,int /*<<< orphan*/ ,struct ib_udata*) ;} ;
struct TYPE_5__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 struct ib_mr* ERR_PTR (int /*<<< orphan*/ ) ; 
 int IB_MR_TYPE_INTEGRITY ; 
 int /*<<< orphan*/  IS_ERR (struct ib_mr*) ; 
 int /*<<< orphan*/  RDMA_RESTRACK_MR ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_restrack_kadd (TYPE_3__*) ; 
 struct ib_mr* stub1 (struct ib_pd*,int,int /*<<< orphan*/ ,struct ib_udata*) ; 

struct ib_mr *ib_alloc_mr_user(struct ib_pd *pd, enum ib_mr_type mr_type,
			       u32 max_num_sg, struct ib_udata *udata)
{
	struct ib_mr *mr;

	if (!pd->device->ops.alloc_mr)
		return ERR_PTR(-EOPNOTSUPP);

	if (WARN_ON_ONCE(mr_type == IB_MR_TYPE_INTEGRITY))
		return ERR_PTR(-EINVAL);

	mr = pd->device->ops.alloc_mr(pd, mr_type, max_num_sg, udata);
	if (!IS_ERR(mr)) {
		mr->device  = pd->device;
		mr->pd      = pd;
		mr->dm      = NULL;
		mr->uobject = NULL;
		atomic_inc(&pd->usecnt);
		mr->need_inval = false;
		mr->res.type = RDMA_RESTRACK_MR;
		rdma_restrack_kadd(&mr->res);
		mr->type = mr_type;
		mr->sig_attrs = NULL;
	}

	return mr;
}