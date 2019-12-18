#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct t4_cqe {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  qid; } ;
struct TYPE_6__ {TYPE_2__ sq; } ;
struct TYPE_4__ {int /*<<< orphan*/  rcq; int /*<<< orphan*/  scq; } ;
struct c4iw_qp {int /*<<< orphan*/  ibqp; TYPE_3__ wq; TYPE_1__ attr; } ;
struct c4iw_dev {int /*<<< orphan*/  qps; } ;
struct c4iw_cq {int /*<<< orphan*/  wait; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 scalar_t__ CQE_OPCODE (struct t4_cqe*) ; 
 int /*<<< orphan*/  CQE_QPID (struct t4_cqe*) ; 
 int CQE_STATUS (struct t4_cqe*) ; 
 int /*<<< orphan*/  CQE_TYPE (struct t4_cqe*) ; 
 int /*<<< orphan*/  CQE_WRID_HI (struct t4_cqe*) ; 
 int /*<<< orphan*/  CQE_WRID_LOW (struct t4_cqe*) ; 
 scalar_t__ FW_RI_RDMA_WRITE ; 
 int /*<<< orphan*/  IB_EVENT_DEVICE_FATAL ; 
 int /*<<< orphan*/  IB_EVENT_QP_ACCESS_ERR ; 
 int /*<<< orphan*/  IB_EVENT_QP_FATAL ; 
 int /*<<< orphan*/  IB_EVENT_QP_REQ_ERR ; 
 scalar_t__ RQ_TYPE (struct t4_cqe*) ; 
 scalar_t__ SQ_TYPE (struct t4_cqe*) ; 
#define  T4_ERR_ACCESS 155 
#define  T4_ERR_BOUND 154 
#define  T4_ERR_CRC 153 
#define  T4_ERR_DDP_QUEUE_NUM 152 
#define  T4_ERR_DDP_VERSION 151 
#define  T4_ERR_ECC 150 
#define  T4_ERR_ECC_PSTAG 149 
#define  T4_ERR_INTERNAL_ERR 148 
#define  T4_ERR_INVALIDATE_MR_WITH_MW_BOUND 147 
#define  T4_ERR_INVALIDATE_SHARED_MR 146 
#define  T4_ERR_IRD_OVERFLOW 145 
#define  T4_ERR_MARKER 144 
#define  T4_ERR_MO 143 
#define  T4_ERR_MSN 142 
#define  T4_ERR_MSN_GAP 141 
#define  T4_ERR_MSN_RANGE 140 
#define  T4_ERR_OPCODE 139 
#define  T4_ERR_OUT_OF_RQE 138 
#define  T4_ERR_PBL_ADDR_BOUND 137 
#define  T4_ERR_PDID 136 
#define  T4_ERR_PDU_LEN_ERR 135 
#define  T4_ERR_QPID 134 
#define  T4_ERR_RDMA_VERSION 133 
#define  T4_ERR_RQE_ADDR_BOUND 132 
#define  T4_ERR_STAG 131 
#define  T4_ERR_SUCCESS 130 
#define  T4_ERR_TBIT 129 
#define  T4_ERR_WRAP 128 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c4iw_qp_add_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c4iw_qp_rem_ref (int /*<<< orphan*/ *) ; 
 struct c4iw_cq* get_chp (struct c4iw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  post_qp_event (struct c4iw_dev*,struct c4iw_cq*,struct c4iw_qp*,struct t4_cqe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 struct c4iw_qp* xa_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_unlock_irq (int /*<<< orphan*/ *) ; 

void c4iw_ev_dispatch(struct c4iw_dev *dev, struct t4_cqe *err_cqe)
{
	struct c4iw_cq *chp;
	struct c4iw_qp *qhp;
	u32 cqid;

	xa_lock_irq(&dev->qps);
	qhp = xa_load(&dev->qps, CQE_QPID(err_cqe));
	if (!qhp) {
		pr_err("BAD AE qpid 0x%x opcode %d status 0x%x type %d wrid.hi 0x%x wrid.lo 0x%x\n",
		       CQE_QPID(err_cqe),
		       CQE_OPCODE(err_cqe), CQE_STATUS(err_cqe),
		       CQE_TYPE(err_cqe), CQE_WRID_HI(err_cqe),
		       CQE_WRID_LOW(err_cqe));
		xa_unlock_irq(&dev->qps);
		goto out;
	}

	if (SQ_TYPE(err_cqe))
		cqid = qhp->attr.scq;
	else
		cqid = qhp->attr.rcq;
	chp = get_chp(dev, cqid);
	if (!chp) {
		pr_err("BAD AE cqid 0x%x qpid 0x%x opcode %d status 0x%x type %d wrid.hi 0x%x wrid.lo 0x%x\n",
		       cqid, CQE_QPID(err_cqe),
		       CQE_OPCODE(err_cqe), CQE_STATUS(err_cqe),
		       CQE_TYPE(err_cqe), CQE_WRID_HI(err_cqe),
		       CQE_WRID_LOW(err_cqe));
		xa_unlock_irq(&dev->qps);
		goto out;
	}

	c4iw_qp_add_ref(&qhp->ibqp);
	atomic_inc(&chp->refcnt);
	xa_unlock_irq(&dev->qps);

	/* Bad incoming write */
	if (RQ_TYPE(err_cqe) &&
	    (CQE_OPCODE(err_cqe) == FW_RI_RDMA_WRITE)) {
		post_qp_event(dev, chp, qhp, err_cqe, IB_EVENT_QP_REQ_ERR);
		goto done;
	}

	switch (CQE_STATUS(err_cqe)) {

	/* Completion Events */
	case T4_ERR_SUCCESS:
		pr_err("AE with status 0!\n");
		break;

	case T4_ERR_STAG:
	case T4_ERR_PDID:
	case T4_ERR_QPID:
	case T4_ERR_ACCESS:
	case T4_ERR_WRAP:
	case T4_ERR_BOUND:
	case T4_ERR_INVALIDATE_SHARED_MR:
	case T4_ERR_INVALIDATE_MR_WITH_MW_BOUND:
		post_qp_event(dev, chp, qhp, err_cqe, IB_EVENT_QP_ACCESS_ERR);
		break;

	/* Device Fatal Errors */
	case T4_ERR_ECC:
	case T4_ERR_ECC_PSTAG:
	case T4_ERR_INTERNAL_ERR:
		post_qp_event(dev, chp, qhp, err_cqe, IB_EVENT_DEVICE_FATAL);
		break;

	/* QP Fatal Errors */
	case T4_ERR_OUT_OF_RQE:
	case T4_ERR_PBL_ADDR_BOUND:
	case T4_ERR_CRC:
	case T4_ERR_MARKER:
	case T4_ERR_PDU_LEN_ERR:
	case T4_ERR_DDP_VERSION:
	case T4_ERR_RDMA_VERSION:
	case T4_ERR_OPCODE:
	case T4_ERR_DDP_QUEUE_NUM:
	case T4_ERR_MSN:
	case T4_ERR_TBIT:
	case T4_ERR_MO:
	case T4_ERR_MSN_GAP:
	case T4_ERR_MSN_RANGE:
	case T4_ERR_RQE_ADDR_BOUND:
	case T4_ERR_IRD_OVERFLOW:
		post_qp_event(dev, chp, qhp, err_cqe, IB_EVENT_QP_FATAL);
		break;

	default:
		pr_err("Unknown T4 status 0x%x QPID 0x%x\n",
		       CQE_STATUS(err_cqe), qhp->wq.sq.qid);
		post_qp_event(dev, chp, qhp, err_cqe, IB_EVENT_QP_FATAL);
		break;
	}
done:
	if (atomic_dec_and_test(&chp->refcnt))
		wake_up(&chp->wait);
	c4iw_qp_rem_ref(&qhp->ibqp);
out:
	return;
}