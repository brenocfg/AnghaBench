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
struct ib_udata {int dummy; } ;
struct ib_cq {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 

__attribute__((used)) static int iwch_resize_cq(struct ib_cq *cq, int cqe, struct ib_udata *udata)
{
#ifdef notyet
	struct iwch_cq *chp = to_iwch_cq(cq);
	struct t3_cq oldcq, newcq;
	int ret;

	pr_debug("%s ib_cq %p cqe %d\n", __func__, cq, cqe);

	/* We don't downsize... */
	if (cqe <= cq->cqe)
		return 0;

	/* create new t3_cq with new size */
	cqe = roundup_pow_of_two(cqe+1);
	newcq.size_log2 = ilog2(cqe);

	/* Dont allow resize to less than the current wce count */
	if (cqe < Q_COUNT(chp->cq.rptr, chp->cq.wptr)) {
		return -ENOMEM;
	}

	/* Quiesce all QPs using this CQ */
	ret = iwch_quiesce_qps(chp);
	if (ret) {
		return ret;
	}

	ret = cxio_create_cq(&chp->rhp->rdev, &newcq);
	if (ret) {
		return ret;
	}

	/* copy CQEs */
	memcpy(newcq.queue, chp->cq.queue, (1 << chp->cq.size_log2) *
				        sizeof(struct t3_cqe));

	/* old iwch_qp gets new t3_cq but keeps old cqid */
	oldcq = chp->cq;
	chp->cq = newcq;
	chp->cq.cqid = oldcq.cqid;

	/* resize new t3_cq to update the HW context */
	ret = cxio_resize_cq(&chp->rhp->rdev, &chp->cq);
	if (ret) {
		chp->cq = oldcq;
		return ret;
	}
	chp->ibcq.cqe = (1<<chp->cq.size_log2) - 1;

	/* destroy old t3_cq */
	oldcq.cqid = newcq.cqid;
	ret = cxio_destroy_cq(&chp->rhp->rdev, &oldcq);
	if (ret) {
		pr_err("%s - cxio_destroy_cq failed %d\n", __func__, ret);
	}

	/* add user hooks here */

	/* resume qps */
	ret = iwch_resume_qps(chp);
	return ret;
#else
	return -ENOSYS;
#endif
}