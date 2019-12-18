#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct mthca_srq {scalar_t__ max; int /*<<< orphan*/  mutex; int /*<<< orphan*/  srqn; } ;
struct mthca_dev {int dummy; } ;
struct ib_udata {int dummy; } ;
struct ib_srq_attr {scalar_t__ srq_limit; } ;
struct ib_srq {int /*<<< orphan*/  device; } ;
typedef  enum ib_srq_attr_mask { ____Placeholder_ib_srq_attr_mask } ib_srq_attr_mask ;

/* Variables and functions */
 int EINVAL ; 
 int IB_SRQ_LIMIT ; 
 int IB_SRQ_MAX_WR ; 
 int mthca_ARM_SRQ (struct mthca_dev*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ mthca_is_memfree (struct mthca_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mthca_dev* to_mdev (int /*<<< orphan*/ ) ; 
 struct mthca_srq* to_msrq (struct ib_srq*) ; 

int mthca_modify_srq(struct ib_srq *ibsrq, struct ib_srq_attr *attr,
		     enum ib_srq_attr_mask attr_mask, struct ib_udata *udata)
{
	struct mthca_dev *dev = to_mdev(ibsrq->device);
	struct mthca_srq *srq = to_msrq(ibsrq);
	int ret = 0;

	/* We don't support resizing SRQs (yet?) */
	if (attr_mask & IB_SRQ_MAX_WR)
		return -EINVAL;

	if (attr_mask & IB_SRQ_LIMIT) {
		u32 max_wr = mthca_is_memfree(dev) ? srq->max - 1 : srq->max;
		if (attr->srq_limit > max_wr)
			return -EINVAL;

		mutex_lock(&srq->mutex);
		ret = mthca_ARM_SRQ(dev, srq->srqn, attr->srq_limit);
		mutex_unlock(&srq->mutex);
	}

	return ret;
}