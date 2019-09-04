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
struct TYPE_6__ {int /*<<< orphan*/  (* notify_new_ah ) (int /*<<< orphan*/ ,struct rdma_ah_attr*,struct rvt_ah*) ;} ;
struct TYPE_4__ {scalar_t__ max_ah; } ;
struct TYPE_5__ {TYPE_1__ props; } ;
struct rvt_dev_info {scalar_t__ n_ahs_allocated; TYPE_3__ driver_f; int /*<<< orphan*/  n_ahs_lock; TYPE_2__ dparms; } ;
struct ib_ah {int dummy; } ;
struct rvt_ah {struct ib_ah ibah; int /*<<< orphan*/  refcount; int /*<<< orphan*/  attr; } ;
struct rdma_ah_attr {int dummy; } ;
struct ib_udata {int dummy; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct ib_ah* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rvt_dev_info* ib_to_rvt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rvt_ah*) ; 
 struct rvt_ah* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_copy_ah_attr (int /*<<< orphan*/ *,struct rdma_ah_attr*) ; 
 scalar_t__ rvt_check_ah (int /*<<< orphan*/ ,struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct rdma_ah_attr*,struct rvt_ah*) ; 

struct ib_ah *rvt_create_ah(struct ib_pd *pd,
			    struct rdma_ah_attr *ah_attr,
			    struct ib_udata *udata)
{
	struct rvt_ah *ah;
	struct rvt_dev_info *dev = ib_to_rvt(pd->device);
	unsigned long flags;

	if (rvt_check_ah(pd->device, ah_attr))
		return ERR_PTR(-EINVAL);

	ah = kmalloc(sizeof(*ah), GFP_ATOMIC);
	if (!ah)
		return ERR_PTR(-ENOMEM);

	spin_lock_irqsave(&dev->n_ahs_lock, flags);
	if (dev->n_ahs_allocated == dev->dparms.props.max_ah) {
		spin_unlock_irqrestore(&dev->n_ahs_lock, flags);
		kfree(ah);
		return ERR_PTR(-ENOMEM);
	}

	dev->n_ahs_allocated++;
	spin_unlock_irqrestore(&dev->n_ahs_lock, flags);

	rdma_copy_ah_attr(&ah->attr, ah_attr);

	atomic_set(&ah->refcount, 0);

	if (dev->driver_f.notify_new_ah)
		dev->driver_f.notify_new_ah(pd->device, ah_attr, ah);

	return &ah->ibah;
}