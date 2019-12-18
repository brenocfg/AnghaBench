#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_11__ {scalar_t__ size; scalar_t__ max_sge; int /*<<< orphan*/  lock; int /*<<< orphan*/  wq; } ;
struct rvt_srq {TYPE_4__ rq; TYPE_5__* ip; int /*<<< orphan*/  limit; } ;
struct rvt_rwqe {int dummy; } ;
struct rvt_rwq {int dummy; } ;
struct TYPE_9__ {scalar_t__ max_srq_sge; scalar_t__ max_srq_wr; scalar_t__ max_srq; } ;
struct TYPE_10__ {TYPE_2__ props; int /*<<< orphan*/  node; } ;
struct rvt_dev_info {scalar_t__ n_srqs_allocated; int /*<<< orphan*/  pending_lock; int /*<<< orphan*/  pending_mmaps; int /*<<< orphan*/  n_srqs_lock; TYPE_3__ dparms; } ;
struct ib_udata {int outlen; } ;
struct TYPE_8__ {scalar_t__ max_sge; scalar_t__ max_wr; int /*<<< orphan*/  srq_limit; } ;
struct ib_srq_init_attr {scalar_t__ srq_type; TYPE_1__ attr; } ;
struct ib_srq {int /*<<< orphan*/  device; } ;
struct ib_sge {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;
struct TYPE_12__ {int /*<<< orphan*/  pending_mmaps; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 scalar_t__ IB_SRQT_BASIC ; 
 int ib_copy_to_udata (struct ib_udata*,int /*<<< orphan*/ *,int) ; 
 struct rvt_dev_info* ib_to_rvt (int /*<<< orphan*/ ) ; 
 struct rvt_srq* ibsrq_to_rvtsrq (struct ib_srq*) ; 
 int /*<<< orphan*/  kfree (TYPE_5__*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ rvt_alloc_rq (TYPE_4__*,int,int /*<<< orphan*/ ,struct ib_udata*) ; 
 TYPE_5__* rvt_create_mmap_info (struct rvt_dev_info*,int,struct ib_udata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvt_free_rq (TYPE_4__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int rvt_create_srq(struct ib_srq *ibsrq, struct ib_srq_init_attr *srq_init_attr,
		   struct ib_udata *udata)
{
	struct rvt_dev_info *dev = ib_to_rvt(ibsrq->device);
	struct rvt_srq *srq = ibsrq_to_rvtsrq(ibsrq);
	u32 sz;
	int ret;

	if (srq_init_attr->srq_type != IB_SRQT_BASIC)
		return -EOPNOTSUPP;

	if (srq_init_attr->attr.max_sge == 0 ||
	    srq_init_attr->attr.max_sge > dev->dparms.props.max_srq_sge ||
	    srq_init_attr->attr.max_wr == 0 ||
	    srq_init_attr->attr.max_wr > dev->dparms.props.max_srq_wr)
		return -EINVAL;

	/*
	 * Need to use vmalloc() if we want to support large #s of entries.
	 */
	srq->rq.size = srq_init_attr->attr.max_wr + 1;
	srq->rq.max_sge = srq_init_attr->attr.max_sge;
	sz = sizeof(struct ib_sge) * srq->rq.max_sge +
		sizeof(struct rvt_rwqe);
	if (rvt_alloc_rq(&srq->rq, srq->rq.size * sz,
			 dev->dparms.node, udata)) {
		ret = -ENOMEM;
		goto bail_srq;
	}

	/*
	 * Return the address of the RWQ as the offset to mmap.
	 * See rvt_mmap() for details.
	 */
	if (udata && udata->outlen >= sizeof(__u64)) {
		u32 s = sizeof(struct rvt_rwq) + srq->rq.size * sz;

		srq->ip = rvt_create_mmap_info(dev, s, udata, srq->rq.wq);
		if (!srq->ip) {
			ret = -ENOMEM;
			goto bail_wq;
		}

		ret = ib_copy_to_udata(udata, &srq->ip->offset,
				       sizeof(srq->ip->offset));
		if (ret)
			goto bail_ip;
	}

	/*
	 * ib_create_srq() will initialize srq->ibsrq.
	 */
	spin_lock_init(&srq->rq.lock);
	srq->limit = srq_init_attr->attr.srq_limit;

	spin_lock(&dev->n_srqs_lock);
	if (dev->n_srqs_allocated == dev->dparms.props.max_srq) {
		spin_unlock(&dev->n_srqs_lock);
		ret = -ENOMEM;
		goto bail_ip;
	}

	dev->n_srqs_allocated++;
	spin_unlock(&dev->n_srqs_lock);

	if (srq->ip) {
		spin_lock_irq(&dev->pending_lock);
		list_add(&srq->ip->pending_mmaps, &dev->pending_mmaps);
		spin_unlock_irq(&dev->pending_lock);
	}

	return 0;

bail_ip:
	kfree(srq->ip);
bail_wq:
	rvt_free_rq(&srq->rq);
bail_srq:
	return ret;
}