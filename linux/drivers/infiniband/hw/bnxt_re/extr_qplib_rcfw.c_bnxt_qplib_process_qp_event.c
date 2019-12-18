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
typedef  size_t u32 ;
typedef  size_t u16 ;
struct creq_qp_event {int event; int /*<<< orphan*/  cookie; } ;
struct creq_qp_error_notification {int /*<<< orphan*/  res_err_state_reason; int /*<<< orphan*/  req_err_state_reason; int /*<<< orphan*/  xid; } ;
struct bnxt_qplib_hwq {int /*<<< orphan*/  lock; int /*<<< orphan*/  cons; } ;
struct bnxt_qplib_rcfw {size_t cmdq_depth; int /*<<< orphan*/  waitq; TYPE_2__* pdev; int /*<<< orphan*/  cmdq_bitmap; struct bnxt_qplib_crsq* crsqe_tbl; int /*<<< orphan*/  (* aeq_handler ) (struct bnxt_qplib_rcfw*,struct creq_qp_event*,struct bnxt_qplib_qp*) ;TYPE_1__* qp_tbl; struct bnxt_qplib_hwq cmdq; } ;
struct bnxt_qplib_qp {int dummy; } ;
struct bnxt_qplib_crsq {int /*<<< orphan*/  req_size; TYPE_3__* resp; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_6__ {int /*<<< orphan*/  cookie; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {struct bnxt_qplib_qp* qp_handle; } ;

/* Variables and functions */
#define  CREQ_QP_EVENT_EVENT_QP_ERROR_NOTIFICATION 128 
 size_t RCFW_CMD_IS_BLOCKING ; 
 size_t RCFW_MAX_COOKIE_VALUE ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  bnxt_qplib_mark_qp_error (struct bnxt_qplib_qp*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,size_t) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,struct creq_qp_event*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave_nested (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct bnxt_qplib_rcfw*,struct creq_qp_event*,struct bnxt_qplib_qp*) ; 
 int /*<<< orphan*/  test_and_clear_bit (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnxt_qplib_process_qp_event(struct bnxt_qplib_rcfw *rcfw,
				       struct creq_qp_event *qp_event)
{
	struct bnxt_qplib_hwq *cmdq = &rcfw->cmdq;
	struct creq_qp_error_notification *err_event;
	struct bnxt_qplib_crsq *crsqe;
	unsigned long flags;
	struct bnxt_qplib_qp *qp;
	u16 cbit, blocked = 0;
	u16 cookie;
	__le16  mcookie;
	u32 qp_id;

	switch (qp_event->event) {
	case CREQ_QP_EVENT_EVENT_QP_ERROR_NOTIFICATION:
		err_event = (struct creq_qp_error_notification *)qp_event;
		qp_id = le32_to_cpu(err_event->xid);
		qp = rcfw->qp_tbl[qp_id].qp_handle;
		dev_dbg(&rcfw->pdev->dev,
			"Received QP error notification\n");
		dev_dbg(&rcfw->pdev->dev,
			"qpid 0x%x, req_err=0x%x, resp_err=0x%x\n",
			qp_id, err_event->req_err_state_reason,
			err_event->res_err_state_reason);
		if (!qp)
			break;
		bnxt_qplib_mark_qp_error(qp);
		rcfw->aeq_handler(rcfw, qp_event, qp);
		break;
	default:
		/*
		 * Command Response
		 * cmdq->lock needs to be acquired to synchronie
		 * the command send and completion reaping. This function
		 * is always called with creq->lock held. Using
		 * the nested variant of spin_lock.
		 *
		 */

		spin_lock_irqsave_nested(&cmdq->lock, flags,
					 SINGLE_DEPTH_NESTING);
		cookie = le16_to_cpu(qp_event->cookie);
		mcookie = qp_event->cookie;
		blocked = cookie & RCFW_CMD_IS_BLOCKING;
		cookie &= RCFW_MAX_COOKIE_VALUE;
		cbit = cookie % rcfw->cmdq_depth;
		crsqe = &rcfw->crsqe_tbl[cbit];
		if (crsqe->resp &&
		    crsqe->resp->cookie  == mcookie) {
			memcpy(crsqe->resp, qp_event, sizeof(*qp_event));
			crsqe->resp = NULL;
		} else {
			if (crsqe->resp && crsqe->resp->cookie)
				dev_err(&rcfw->pdev->dev,
					"CMD %s cookie sent=%#x, recd=%#x\n",
					crsqe->resp ? "mismatch" : "collision",
					crsqe->resp ? crsqe->resp->cookie : 0,
					mcookie);
		}
		if (!test_and_clear_bit(cbit, rcfw->cmdq_bitmap))
			dev_warn(&rcfw->pdev->dev,
				 "CMD bit %d was not requested\n", cbit);
		cmdq->cons += crsqe->req_size;
		crsqe->req_size = 0;

		if (!blocked)
			wake_up(&rcfw->waitq);
		spin_unlock_irqrestore(&cmdq->lock, flags);
	}
	return 0;
}