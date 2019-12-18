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
struct rdma_cqe_requester {int status; int /*<<< orphan*/  sq_cons; } ;
struct qedr_qp {int /*<<< orphan*/  icid; int /*<<< orphan*/  state; } ;
struct qedr_dev {int dummy; } ;
struct qedr_cq {int /*<<< orphan*/  icid; } ;
struct ib_wc {int dummy; } ;
typedef  enum ib_wc_status { ____Placeholder_ib_wc_status } ib_wc_status ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DEBUG (struct qedr_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IB_WC_BAD_RESP_ERR ; 
 int IB_WC_GENERAL_ERR ; 
 int IB_WC_LOC_LEN_ERR ; 
 int IB_WC_LOC_PROT_ERR ; 
 int IB_WC_LOC_QP_OP_ERR ; 
 int IB_WC_MW_BIND_ERR ; 
 int IB_WC_REM_ACCESS_ERR ; 
 int IB_WC_REM_INV_REQ_ERR ; 
 int IB_WC_REM_OP_ERR ; 
 int IB_WC_RETRY_EXC_ERR ; 
 int IB_WC_RNR_RETRY_EXC_ERR ; 
 int IB_WC_SUCCESS ; 
 int IB_WC_WR_FLUSH_ERR ; 
 int /*<<< orphan*/  QEDR_MSG_CQ ; 
 int /*<<< orphan*/  QED_ROCE_QP_STATE_ERR ; 
#define  RDMA_CQE_REQ_STS_BAD_RESPONSE_ERR 139 
#define  RDMA_CQE_REQ_STS_LOCAL_LENGTH_ERR 138 
#define  RDMA_CQE_REQ_STS_LOCAL_PROTECTION_ERR 137 
#define  RDMA_CQE_REQ_STS_LOCAL_QP_OPERATION_ERR 136 
#define  RDMA_CQE_REQ_STS_MEMORY_MGT_OPERATION_ERR 135 
#define  RDMA_CQE_REQ_STS_OK 134 
#define  RDMA_CQE_REQ_STS_REMOTE_ACCESS_ERR 133 
#define  RDMA_CQE_REQ_STS_REMOTE_INVALID_REQUEST_ERR 132 
#define  RDMA_CQE_REQ_STS_REMOTE_OPERATION_ERR 131 
#define  RDMA_CQE_REQ_STS_RNR_NAK_RETRY_CNT_ERR 130 
#define  RDMA_CQE_REQ_STS_TRANSPORT_RETRY_CNT_ERR 129 
#define  RDMA_CQE_REQ_STS_WORK_REQUEST_FLUSHED_ERR 128 
 int process_req (struct qedr_dev*,struct qedr_qp*,struct qedr_cq*,int,struct ib_wc*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int qedr_poll_cq_req(struct qedr_dev *dev,
			    struct qedr_qp *qp, struct qedr_cq *cq,
			    int num_entries, struct ib_wc *wc,
			    struct rdma_cqe_requester *req)
{
	int cnt = 0;

	switch (req->status) {
	case RDMA_CQE_REQ_STS_OK:
		cnt = process_req(dev, qp, cq, num_entries, wc, req->sq_cons,
				  IB_WC_SUCCESS, 0);
		break;
	case RDMA_CQE_REQ_STS_WORK_REQUEST_FLUSHED_ERR:
		if (qp->state != QED_ROCE_QP_STATE_ERR)
			DP_DEBUG(dev, QEDR_MSG_CQ,
				 "Error: POLL CQ with RDMA_CQE_REQ_STS_WORK_REQUEST_FLUSHED_ERR. CQ icid=0x%x, QP icid=0x%x\n",
				 cq->icid, qp->icid);
		cnt = process_req(dev, qp, cq, num_entries, wc, req->sq_cons,
				  IB_WC_WR_FLUSH_ERR, 1);
		break;
	default:
		/* process all WQE before the cosumer */
		qp->state = QED_ROCE_QP_STATE_ERR;
		cnt = process_req(dev, qp, cq, num_entries, wc,
				  req->sq_cons - 1, IB_WC_SUCCESS, 0);
		wc += cnt;
		/* if we have extra WC fill it with actual error info */
		if (cnt < num_entries) {
			enum ib_wc_status wc_status;

			switch (req->status) {
			case RDMA_CQE_REQ_STS_BAD_RESPONSE_ERR:
				DP_ERR(dev,
				       "Error: POLL CQ with RDMA_CQE_REQ_STS_BAD_RESPONSE_ERR. CQ icid=0x%x, QP icid=0x%x\n",
				       cq->icid, qp->icid);
				wc_status = IB_WC_BAD_RESP_ERR;
				break;
			case RDMA_CQE_REQ_STS_LOCAL_LENGTH_ERR:
				DP_ERR(dev,
				       "Error: POLL CQ with RDMA_CQE_REQ_STS_LOCAL_LENGTH_ERR. CQ icid=0x%x, QP icid=0x%x\n",
				       cq->icid, qp->icid);
				wc_status = IB_WC_LOC_LEN_ERR;
				break;
			case RDMA_CQE_REQ_STS_LOCAL_QP_OPERATION_ERR:
				DP_ERR(dev,
				       "Error: POLL CQ with RDMA_CQE_REQ_STS_LOCAL_QP_OPERATION_ERR. CQ icid=0x%x, QP icid=0x%x\n",
				       cq->icid, qp->icid);
				wc_status = IB_WC_LOC_QP_OP_ERR;
				break;
			case RDMA_CQE_REQ_STS_LOCAL_PROTECTION_ERR:
				DP_ERR(dev,
				       "Error: POLL CQ with RDMA_CQE_REQ_STS_LOCAL_PROTECTION_ERR. CQ icid=0x%x, QP icid=0x%x\n",
				       cq->icid, qp->icid);
				wc_status = IB_WC_LOC_PROT_ERR;
				break;
			case RDMA_CQE_REQ_STS_MEMORY_MGT_OPERATION_ERR:
				DP_ERR(dev,
				       "Error: POLL CQ with RDMA_CQE_REQ_STS_MEMORY_MGT_OPERATION_ERR. CQ icid=0x%x, QP icid=0x%x\n",
				       cq->icid, qp->icid);
				wc_status = IB_WC_MW_BIND_ERR;
				break;
			case RDMA_CQE_REQ_STS_REMOTE_INVALID_REQUEST_ERR:
				DP_ERR(dev,
				       "Error: POLL CQ with RDMA_CQE_REQ_STS_REMOTE_INVALID_REQUEST_ERR. CQ icid=0x%x, QP icid=0x%x\n",
				       cq->icid, qp->icid);
				wc_status = IB_WC_REM_INV_REQ_ERR;
				break;
			case RDMA_CQE_REQ_STS_REMOTE_ACCESS_ERR:
				DP_ERR(dev,
				       "Error: POLL CQ with RDMA_CQE_REQ_STS_REMOTE_ACCESS_ERR. CQ icid=0x%x, QP icid=0x%x\n",
				       cq->icid, qp->icid);
				wc_status = IB_WC_REM_ACCESS_ERR;
				break;
			case RDMA_CQE_REQ_STS_REMOTE_OPERATION_ERR:
				DP_ERR(dev,
				       "Error: POLL CQ with RDMA_CQE_REQ_STS_REMOTE_OPERATION_ERR. CQ icid=0x%x, QP icid=0x%x\n",
				       cq->icid, qp->icid);
				wc_status = IB_WC_REM_OP_ERR;
				break;
			case RDMA_CQE_REQ_STS_RNR_NAK_RETRY_CNT_ERR:
				DP_ERR(dev,
				       "Error: POLL CQ with RDMA_CQE_REQ_STS_RNR_NAK_RETRY_CNT_ERR. CQ icid=0x%x, QP icid=0x%x\n",
				       cq->icid, qp->icid);
				wc_status = IB_WC_RNR_RETRY_EXC_ERR;
				break;
			case RDMA_CQE_REQ_STS_TRANSPORT_RETRY_CNT_ERR:
				DP_ERR(dev,
				       "Error: POLL CQ with ROCE_CQE_REQ_STS_TRANSPORT_RETRY_CNT_ERR. CQ icid=0x%x, QP icid=0x%x\n",
				       cq->icid, qp->icid);
				wc_status = IB_WC_RETRY_EXC_ERR;
				break;
			default:
				DP_ERR(dev,
				       "Error: POLL CQ with IB_WC_GENERAL_ERR. CQ icid=0x%x, QP icid=0x%x\n",
				       cq->icid, qp->icid);
				wc_status = IB_WC_GENERAL_ERR;
			}
			cnt += process_req(dev, qp, cq, 1, wc, req->sq_cons,
					   wc_status, 1);
		}
	}

	return cnt;
}