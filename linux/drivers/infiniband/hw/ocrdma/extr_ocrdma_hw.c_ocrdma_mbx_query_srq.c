#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dbid; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct ocrdma_srq {TYPE_1__ rq; TYPE_2__ ibsrq; } ;
struct ocrdma_query_srq_rsp {int srq_lmt_max_sge; int max_rqe_pdid; } ;
struct ocrdma_query_srq {int /*<<< orphan*/  id; } ;
struct ocrdma_mqe {int dummy; } ;
struct ocrdma_dev {int dummy; } ;
struct ib_srq_attr {int max_sge; int max_wr; int srq_limit; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  OCRDMA_CMD_QUERY_SRQ ; 
 int OCRDMA_QUERY_SRQ_RSP_MAX_RQE_SHIFT ; 
 int OCRDMA_QUERY_SRQ_RSP_MAX_SGE_RECV_MASK ; 
 int OCRDMA_QUERY_SRQ_RSP_SRQ_LIMIT_SHIFT ; 
 struct ocrdma_dev* get_ocrdma_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ocrdma_query_srq*) ; 
 struct ocrdma_query_srq* ocrdma_init_emb_mqe (int /*<<< orphan*/ ,int) ; 
 int ocrdma_mbx_cmd (struct ocrdma_dev*,struct ocrdma_mqe*) ; 

int ocrdma_mbx_query_srq(struct ocrdma_srq *srq, struct ib_srq_attr *srq_attr)
{
	int status = -ENOMEM;
	struct ocrdma_query_srq *cmd;
	struct ocrdma_dev *dev = get_ocrdma_dev(srq->ibsrq.device);

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_QUERY_SRQ, sizeof(*cmd));
	if (!cmd)
		return status;
	cmd->id = srq->rq.dbid;
	status = ocrdma_mbx_cmd(dev, (struct ocrdma_mqe *)cmd);
	if (status == 0) {
		struct ocrdma_query_srq_rsp *rsp =
		    (struct ocrdma_query_srq_rsp *)cmd;
		srq_attr->max_sge =
		    rsp->srq_lmt_max_sge &
		    OCRDMA_QUERY_SRQ_RSP_MAX_SGE_RECV_MASK;
		srq_attr->max_wr =
		    rsp->max_rqe_pdid >> OCRDMA_QUERY_SRQ_RSP_MAX_RQE_SHIFT;
		srq_attr->srq_limit = rsp->srq_lmt_max_sge >>
		    OCRDMA_QUERY_SRQ_RSP_SRQ_LIMIT_SHIFT;
	}
	kfree(cmd);
	return status;
}