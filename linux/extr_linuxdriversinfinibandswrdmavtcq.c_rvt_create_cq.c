#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {unsigned int max_cqe; scalar_t__ max_cq; } ;
struct TYPE_8__ {int /*<<< orphan*/  node; TYPE_2__ props; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* comp_vect_cpu_lookup ) (struct rvt_dev_info*,int) ;} ;
struct TYPE_5__ {int num_comp_vectors; } ;
struct rvt_dev_info {scalar_t__ n_cqs_allocated; TYPE_4__ dparms; TYPE_3__ driver_f; int /*<<< orphan*/  pending_lock; int /*<<< orphan*/  pending_mmaps; int /*<<< orphan*/  n_cqs_lock; TYPE_1__ ibdev; } ;
struct rvt_cq_wc {int dummy; } ;
struct ib_cq {unsigned int cqe; } ;
struct rvt_cq {struct rvt_cq* ip; struct ib_cq ibcq; struct rvt_cq_wc* queue; int /*<<< orphan*/  comptask; int /*<<< orphan*/  lock; int /*<<< orphan*/  notify; int /*<<< orphan*/  comp_vector_cpu; struct rvt_dev_info* rdi; int /*<<< orphan*/  pending_mmaps; int /*<<< orphan*/  offset; } ;
struct ib_wc {int dummy; } ;
struct ib_uverbs_wc {int dummy; } ;
struct ib_udata {int outlen; } ;
struct ib_ucontext {int dummy; } ;
struct ib_device {int dummy; } ;
struct ib_cq_init_attr {unsigned int cqe; int comp_vector; scalar_t__ flags; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct ib_cq* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RVT_CQ_NONE ; 
 int /*<<< orphan*/  cpumask_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of_node (int /*<<< orphan*/ ) ; 
 int ib_copy_to_udata (struct ib_udata*,int /*<<< orphan*/ *,int) ; 
 struct rvt_dev_info* ib_to_rvt (struct ib_device*) ; 
 int /*<<< orphan*/  kfree (struct rvt_cq*) ; 
 struct rvt_cq* kzalloc_node (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct rvt_cq* rvt_create_mmap_info (struct rvt_dev_info*,int,struct ib_ucontext*,struct rvt_cq_wc*) ; 
 int /*<<< orphan*/  send_complete ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct rvt_dev_info*,int) ; 
 int /*<<< orphan*/  trace_rvt_create_cq (struct rvt_cq*,struct ib_cq_init_attr const*) ; 
 int /*<<< orphan*/  vfree (struct rvt_cq_wc*) ; 
 struct rvt_cq_wc* vmalloc_user (int) ; 
 struct rvt_cq_wc* vzalloc_node (int,int /*<<< orphan*/ ) ; 

struct ib_cq *rvt_create_cq(struct ib_device *ibdev,
			    const struct ib_cq_init_attr *attr,
			    struct ib_ucontext *context,
			    struct ib_udata *udata)
{
	struct rvt_dev_info *rdi = ib_to_rvt(ibdev);
	struct rvt_cq *cq;
	struct rvt_cq_wc *wc;
	struct ib_cq *ret;
	u32 sz;
	unsigned int entries = attr->cqe;
	int comp_vector = attr->comp_vector;

	if (attr->flags)
		return ERR_PTR(-EINVAL);

	if (entries < 1 || entries > rdi->dparms.props.max_cqe)
		return ERR_PTR(-EINVAL);

	if (comp_vector < 0)
		comp_vector = 0;

	comp_vector = comp_vector % rdi->ibdev.num_comp_vectors;

	/* Allocate the completion queue structure. */
	cq = kzalloc_node(sizeof(*cq), GFP_KERNEL, rdi->dparms.node);
	if (!cq)
		return ERR_PTR(-ENOMEM);

	/*
	 * Allocate the completion queue entries and head/tail pointers.
	 * This is allocated separately so that it can be resized and
	 * also mapped into user space.
	 * We need to use vmalloc() in order to support mmap and large
	 * numbers of entries.
	 */
	sz = sizeof(*wc);
	if (udata && udata->outlen >= sizeof(__u64))
		sz += sizeof(struct ib_uverbs_wc) * (entries + 1);
	else
		sz += sizeof(struct ib_wc) * (entries + 1);
	wc = udata ?
		vmalloc_user(sz) :
		vzalloc_node(sz, rdi->dparms.node);
	if (!wc) {
		ret = ERR_PTR(-ENOMEM);
		goto bail_cq;
	}

	/*
	 * Return the address of the WC as the offset to mmap.
	 * See rvt_mmap() for details.
	 */
	if (udata && udata->outlen >= sizeof(__u64)) {
		int err;

		cq->ip = rvt_create_mmap_info(rdi, sz, context, wc);
		if (!cq->ip) {
			ret = ERR_PTR(-ENOMEM);
			goto bail_wc;
		}

		err = ib_copy_to_udata(udata, &cq->ip->offset,
				       sizeof(cq->ip->offset));
		if (err) {
			ret = ERR_PTR(err);
			goto bail_ip;
		}
	}

	spin_lock_irq(&rdi->n_cqs_lock);
	if (rdi->n_cqs_allocated == rdi->dparms.props.max_cq) {
		spin_unlock_irq(&rdi->n_cqs_lock);
		ret = ERR_PTR(-ENOMEM);
		goto bail_ip;
	}

	rdi->n_cqs_allocated++;
	spin_unlock_irq(&rdi->n_cqs_lock);

	if (cq->ip) {
		spin_lock_irq(&rdi->pending_lock);
		list_add(&cq->ip->pending_mmaps, &rdi->pending_mmaps);
		spin_unlock_irq(&rdi->pending_lock);
	}

	/*
	 * ib_create_cq() will initialize cq->ibcq except for cq->ibcq.cqe.
	 * The number of entries should be >= the number requested or return
	 * an error.
	 */
	cq->rdi = rdi;
	if (rdi->driver_f.comp_vect_cpu_lookup)
		cq->comp_vector_cpu =
			rdi->driver_f.comp_vect_cpu_lookup(rdi, comp_vector);
	else
		cq->comp_vector_cpu =
			cpumask_first(cpumask_of_node(rdi->dparms.node));

	cq->ibcq.cqe = entries;
	cq->notify = RVT_CQ_NONE;
	spin_lock_init(&cq->lock);
	INIT_WORK(&cq->comptask, send_complete);
	cq->queue = wc;

	ret = &cq->ibcq;

	trace_rvt_create_cq(cq, attr);
	goto done;

bail_ip:
	kfree(cq->ip);
bail_wc:
	vfree(wc);
bail_cq:
	kfree(cq);
done:
	return ret;
}