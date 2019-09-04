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
struct TYPE_7__ {TYPE_2__* queue; } ;
struct rxe_srq {scalar_t__ limit; TYPE_3__ rq; scalar_t__ error; } ;
struct TYPE_8__ {scalar_t__ max_srq_wr; scalar_t__ max_srq_sge; } ;
struct rxe_dev {TYPE_4__ attr; } ;
struct ib_srq_attr {scalar_t__ max_wr; scalar_t__ srq_limit; scalar_t__ max_sge; } ;
typedef  enum ib_srq_attr_mask { ____Placeholder_ib_srq_attr_mask } ib_srq_attr_mask ;
struct TYPE_6__ {TYPE_1__* buf; } ;
struct TYPE_5__ {scalar_t__ index_mask; } ;

/* Variables and functions */
 int EINVAL ; 
 int IB_SRQ_INIT_MASK ; 
 int IB_SRQ_LIMIT ; 
 int IB_SRQ_MAX_WR ; 
 scalar_t__ RXE_MIN_SRQ_SGE ; 
 scalar_t__ RXE_MIN_SRQ_WR ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 

int rxe_srq_chk_attr(struct rxe_dev *rxe, struct rxe_srq *srq,
		     struct ib_srq_attr *attr, enum ib_srq_attr_mask mask)
{
	if (srq && srq->error) {
		pr_warn("srq in error state\n");
		goto err1;
	}

	if (mask & IB_SRQ_MAX_WR) {
		if (attr->max_wr > rxe->attr.max_srq_wr) {
			pr_warn("max_wr(%d) > max_srq_wr(%d)\n",
				attr->max_wr, rxe->attr.max_srq_wr);
			goto err1;
		}

		if (attr->max_wr <= 0) {
			pr_warn("max_wr(%d) <= 0\n", attr->max_wr);
			goto err1;
		}

		if (srq && srq->limit && (attr->max_wr < srq->limit)) {
			pr_warn("max_wr (%d) < srq->limit (%d)\n",
				attr->max_wr, srq->limit);
			goto err1;
		}

		if (attr->max_wr < RXE_MIN_SRQ_WR)
			attr->max_wr = RXE_MIN_SRQ_WR;
	}

	if (mask & IB_SRQ_LIMIT) {
		if (attr->srq_limit > rxe->attr.max_srq_wr) {
			pr_warn("srq_limit(%d) > max_srq_wr(%d)\n",
				attr->srq_limit, rxe->attr.max_srq_wr);
			goto err1;
		}

		if (srq && (attr->srq_limit > srq->rq.queue->buf->index_mask)) {
			pr_warn("srq_limit (%d) > cur limit(%d)\n",
				attr->srq_limit,
				 srq->rq.queue->buf->index_mask);
			goto err1;
		}
	}

	if (mask == IB_SRQ_INIT_MASK) {
		if (attr->max_sge > rxe->attr.max_srq_sge) {
			pr_warn("max_sge(%d) > max_srq_sge(%d)\n",
				attr->max_sge, rxe->attr.max_srq_sge);
			goto err1;
		}

		if (attr->max_sge < RXE_MIN_SRQ_SGE)
			attr->max_sge = RXE_MIN_SRQ_SGE;
	}

	return 0;

err1:
	return -EINVAL;
}