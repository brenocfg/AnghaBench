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
struct t4_cqe {int dummy; } ;
struct ib_wc {int dummy; } ;
struct c4iw_srq {int /*<<< orphan*/  lock; } ;
struct c4iw_qp {int /*<<< orphan*/  lock; struct c4iw_srq* srq; } ;
struct c4iw_cq {int /*<<< orphan*/  rhp; int /*<<< orphan*/  cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CQE_QPID (struct t4_cqe*) ; 
 int __c4iw_poll_cq_one (struct c4iw_cq*,struct c4iw_qp*,struct ib_wc*,struct c4iw_srq*) ; 
 struct c4iw_qp* get_qhp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int t4_next_cqe (int /*<<< orphan*/ *,struct t4_cqe**) ; 

__attribute__((used)) static int c4iw_poll_cq_one(struct c4iw_cq *chp, struct ib_wc *wc)
{
	struct c4iw_srq *srq = NULL;
	struct c4iw_qp *qhp = NULL;
	struct t4_cqe *rd_cqe;
	int ret;

	ret = t4_next_cqe(&chp->cq, &rd_cqe);

	if (ret)
		return ret;

	qhp = get_qhp(chp->rhp, CQE_QPID(rd_cqe));
	if (qhp) {
		spin_lock(&qhp->lock);
		srq = qhp->srq;
		if (srq)
			spin_lock(&srq->lock);
		ret = __c4iw_poll_cq_one(chp, qhp, wc, srq);
		spin_unlock(&qhp->lock);
		if (srq)
			spin_unlock(&srq->lock);
	} else {
		ret = __c4iw_poll_cq_one(chp, NULL, wc, NULL);
	}
	return ret;
}