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
struct TYPE_8__ {int flushed; } ;
struct TYPE_5__ {int flushed; } ;
struct bnxt_qplib_qp {TYPE_4__ rq; int /*<<< orphan*/  rq_flush; int /*<<< orphan*/  srq; TYPE_1__ sq; int /*<<< orphan*/  sq_flush; struct bnxt_qplib_cq* rcq; struct bnxt_qplib_cq* scq; } ;
struct TYPE_7__ {TYPE_2__* pdev; } ;
struct bnxt_qplib_cq {int /*<<< orphan*/  rqf_head; TYPE_3__ hwq; int /*<<< orphan*/  sqf_head; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_qplib_cancel_phantom_processing (struct bnxt_qplib_qp*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,struct bnxt_qplib_qp*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __bnxt_qplib_add_flush_qp(struct bnxt_qplib_qp *qp)
{
	struct bnxt_qplib_cq *scq, *rcq;

	scq = qp->scq;
	rcq = qp->rcq;

	if (!qp->sq.flushed) {
		dev_dbg(&scq->hwq.pdev->dev,
			"FP: Adding to SQ Flush list = %p\n", qp);
		bnxt_qplib_cancel_phantom_processing(qp);
		list_add_tail(&qp->sq_flush, &scq->sqf_head);
		qp->sq.flushed = true;
	}
	if (!qp->srq) {
		if (!qp->rq.flushed) {
			dev_dbg(&rcq->hwq.pdev->dev,
				"FP: Adding to RQ Flush list = %p\n", qp);
			list_add_tail(&qp->rq_flush, &rcq->rqf_head);
			qp->rq.flushed = true;
		}
	}
}