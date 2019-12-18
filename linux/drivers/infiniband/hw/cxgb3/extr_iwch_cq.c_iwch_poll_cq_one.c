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
struct t3_cqe {int dummy; } ;
struct iwch_qp {int /*<<< orphan*/  lock; } ;
struct iwch_dev {int dummy; } ;
struct iwch_cq {int /*<<< orphan*/  cq; } ;
struct ib_wc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CQE_QPID (struct t3_cqe) ; 
 int __iwch_poll_cq_one (struct iwch_dev*,struct iwch_cq*,struct iwch_qp*,struct ib_wc*) ; 
 struct t3_cqe* cxio_next_cqe (int /*<<< orphan*/ *) ; 
 struct iwch_qp* get_qhp (struct iwch_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwch_poll_cq_one(struct iwch_dev *rhp, struct iwch_cq *chp,
			    struct ib_wc *wc)
{
	struct iwch_qp *qhp;
	struct t3_cqe *rd_cqe;
	int ret;

	rd_cqe = cxio_next_cqe(&chp->cq);

	if (!rd_cqe)
		return 0;

	qhp = get_qhp(rhp, CQE_QPID(*rd_cqe));
	if (qhp) {
		spin_lock(&qhp->lock);
		ret = __iwch_poll_cq_one(rhp, chp, qhp, wc);
		spin_unlock(&qhp->lock);
	} else {
		ret = __iwch_poll_cq_one(rhp, chp, NULL, wc);
	}
	return ret;
}