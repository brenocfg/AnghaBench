#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ state; int /*<<< orphan*/  psn; } ;
struct TYPE_9__ {int /*<<< orphan*/  max_sge; int /*<<< orphan*/  max_wr; } ;
struct TYPE_7__ {int /*<<< orphan*/  max_inline; int /*<<< orphan*/  max_sge; int /*<<< orphan*/  max_wr; } ;
struct TYPE_6__ {int /*<<< orphan*/  psn; } ;
struct TYPE_8__ {int /*<<< orphan*/  max_recv_sge; int /*<<< orphan*/  max_recv_wr; int /*<<< orphan*/  max_inline_data; int /*<<< orphan*/  max_send_sge; int /*<<< orphan*/  max_send_wr; } ;
struct ib_qp_attr {int sq_draining; int /*<<< orphan*/  alt_ah_attr; int /*<<< orphan*/  ah_attr; TYPE_3__ cap; int /*<<< orphan*/  sq_psn; int /*<<< orphan*/  rq_psn; } ;
struct rxe_qp {TYPE_5__ req; int /*<<< orphan*/  alt_av; int /*<<< orphan*/  pri_av; TYPE_4__ rq; int /*<<< orphan*/  srq; TYPE_2__ sq; TYPE_1__ resp; struct ib_qp_attr attr; } ;

/* Variables and functions */
 scalar_t__ QP_STATE_DRAIN ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  rxe_av_to_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int rxe_qp_to_attr(struct rxe_qp *qp, struct ib_qp_attr *attr, int mask)
{
	*attr = qp->attr;

	attr->rq_psn				= qp->resp.psn;
	attr->sq_psn				= qp->req.psn;

	attr->cap.max_send_wr			= qp->sq.max_wr;
	attr->cap.max_send_sge			= qp->sq.max_sge;
	attr->cap.max_inline_data		= qp->sq.max_inline;

	if (!qp->srq) {
		attr->cap.max_recv_wr		= qp->rq.max_wr;
		attr->cap.max_recv_sge		= qp->rq.max_sge;
	}

	rxe_av_to_attr(&qp->pri_av, &attr->ah_attr);
	rxe_av_to_attr(&qp->alt_av, &attr->alt_ah_attr);

	if (qp->req.state == QP_STATE_DRAIN) {
		attr->sq_draining = 1;
		/* applications that get this state
		 * typically spin on it. yield the
		 * processor
		 */
		cond_resched();
	} else {
		attr->sq_draining = 0;
	}

	pr_debug("attr->sq_draining = %d\n", attr->sq_draining);

	return 0;
}