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
struct ib_sig_attrs {int dummy; } ;
struct ib_pd {int /*<<< orphan*/  usecnt; TYPE_2__* device; } ;
struct TYPE_6__ {int /*<<< orphan*/  type; } ;
struct ib_mr {int need_inval; struct ib_sig_attrs* sig_attrs; int /*<<< orphan*/  type; TYPE_3__ res; int /*<<< orphan*/ * uobject; int /*<<< orphan*/ * dm; struct ib_pd* pd; TYPE_2__* device; } ;
struct TYPE_4__ {struct ib_mr* (* alloc_mr_integrity ) (struct ib_pd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  map_mr_sg_pi; } ;
struct TYPE_5__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 struct ib_mr* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_MR_TYPE_INTEGRITY ; 
 scalar_t__ IS_ERR (struct ib_mr*) ; 
 int /*<<< orphan*/  RDMA_RESTRACK_MR ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ib_sig_attrs*) ; 
 struct ib_sig_attrs* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_restrack_kadd (TYPE_3__*) ; 
 struct ib_mr* stub1 (struct ib_pd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct ib_mr *ib_alloc_mr_integrity(struct ib_pd *pd,
				    u32 max_num_data_sg,
				    u32 max_num_meta_sg)
{
	struct ib_mr *mr;
	struct ib_sig_attrs *sig_attrs;

	if (!pd->device->ops.alloc_mr_integrity ||
	    !pd->device->ops.map_mr_sg_pi)
		return ERR_PTR(-EOPNOTSUPP);

	if (!max_num_meta_sg)
		return ERR_PTR(-EINVAL);

	sig_attrs = kzalloc(sizeof(struct ib_sig_attrs), GFP_KERNEL);
	if (!sig_attrs)
		return ERR_PTR(-ENOMEM);

	mr = pd->device->ops.alloc_mr_integrity(pd, max_num_data_sg,
						max_num_meta_sg);
	if (IS_ERR(mr)) {
		kfree(sig_attrs);
		return mr;
	}

	mr->device = pd->device;
	mr->pd = pd;
	mr->dm = NULL;
	mr->uobject = NULL;
	atomic_inc(&pd->usecnt);
	mr->need_inval = false;
	mr->res.type = RDMA_RESTRACK_MR;
	rdma_restrack_kadd(&mr->res);
	mr->type = IB_MR_TYPE_INTEGRITY;
	mr->sig_attrs = sig_attrs;

	return mr;
}