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
struct ocrdma_query_qp_rsp {int /*<<< orphan*/  params; } ;
struct ocrdma_query_qp {int /*<<< orphan*/  qp_id; } ;
struct ocrdma_qp_params {int dummy; } ;
struct ocrdma_qp {int /*<<< orphan*/  id; } ;
struct ocrdma_mqe {int dummy; } ;
struct ocrdma_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  OCRDMA_CMD_QUERY_QP ; 
 int /*<<< orphan*/  kfree (struct ocrdma_query_qp*) ; 
 int /*<<< orphan*/  memcpy (struct ocrdma_qp_params*,int /*<<< orphan*/ *,int) ; 
 struct ocrdma_query_qp* ocrdma_init_emb_mqe (int /*<<< orphan*/ ,int) ; 
 int ocrdma_mbx_cmd (struct ocrdma_dev*,struct ocrdma_mqe*) ; 

int ocrdma_mbx_query_qp(struct ocrdma_dev *dev, struct ocrdma_qp *qp,
			struct ocrdma_qp_params *param)
{
	int status = -ENOMEM;
	struct ocrdma_query_qp *cmd;
	struct ocrdma_query_qp_rsp *rsp;

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_QUERY_QP, sizeof(*rsp));
	if (!cmd)
		return status;
	cmd->qp_id = qp->id;
	status = ocrdma_mbx_cmd(dev, (struct ocrdma_mqe *)cmd);
	if (status)
		goto mbx_err;
	rsp = (struct ocrdma_query_qp_rsp *)cmd;
	memcpy(param, &rsp->params, sizeof(struct ocrdma_qp_params));
mbx_err:
	kfree(cmd);
	return status;
}