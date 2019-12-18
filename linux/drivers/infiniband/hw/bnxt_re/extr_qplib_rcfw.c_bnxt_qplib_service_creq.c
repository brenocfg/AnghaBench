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
typedef  scalar_t__ u32 ;
struct creq_qp_event {int dummy; } ;
struct creq_func_event {int dummy; } ;
struct creq_base {scalar_t__ type; } ;
struct bnxt_qplib_hwq {scalar_t__ cons; int /*<<< orphan*/  lock; int /*<<< orphan*/  max_elements; scalar_t__ pbl_ptr; } ;
struct bnxt_qplib_rcfw {int /*<<< orphan*/  creq_ring_id; int /*<<< orphan*/  creq_bar_reg_iomem; TYPE_2__* pdev; int /*<<< orphan*/  creq_func_event_processed; int /*<<< orphan*/  creq_qp_event_processed; struct bnxt_qplib_hwq creq; TYPE_1__* res; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  cctx; } ;

/* Variables and functions */
 scalar_t__ ASYNC_EVENT_CMPL_TYPE_HWRM_ASYNC_EVENT ; 
#define  CREQ_BASE_TYPE_FUNC_EVENT 129 
 scalar_t__ CREQ_BASE_TYPE_MASK ; 
#define  CREQ_BASE_TYPE_QP_EVENT 128 
 int /*<<< orphan*/  CREQ_CMP_VALID (struct creq_base*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ CREQ_ENTRY_POLL_BUDGET ; 
 scalar_t__ HWQ_CMP (scalar_t__,struct bnxt_qplib_hwq*) ; 
 int bnxt_qplib_is_chip_gen_p5 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_qplib_process_func_event (struct bnxt_qplib_rcfw*,struct creq_func_event*) ; 
 int /*<<< orphan*/  bnxt_qplib_process_qp_event (struct bnxt_qplib_rcfw*,struct creq_qp_event*) ; 
 int /*<<< orphan*/  bnxt_qplib_ring_creq_db_rearm (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 size_t get_creq_idx (scalar_t__) ; 
 size_t get_creq_pg (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void bnxt_qplib_service_creq(unsigned long data)
{
	struct bnxt_qplib_rcfw *rcfw = (struct bnxt_qplib_rcfw *)data;
	bool gen_p5 = bnxt_qplib_is_chip_gen_p5(rcfw->res->cctx);
	struct bnxt_qplib_hwq *creq = &rcfw->creq;
	u32 type, budget = CREQ_ENTRY_POLL_BUDGET;
	struct creq_base *creqe, **creq_ptr;
	u32 sw_cons, raw_cons;
	unsigned long flags;

	/* Service the CREQ until budget is over */
	spin_lock_irqsave(&creq->lock, flags);
	raw_cons = creq->cons;
	while (budget > 0) {
		sw_cons = HWQ_CMP(raw_cons, creq);
		creq_ptr = (struct creq_base **)creq->pbl_ptr;
		creqe = &creq_ptr[get_creq_pg(sw_cons)][get_creq_idx(sw_cons)];
		if (!CREQ_CMP_VALID(creqe, raw_cons, creq->max_elements))
			break;
		/* The valid test of the entry must be done first before
		 * reading any further.
		 */
		dma_rmb();

		type = creqe->type & CREQ_BASE_TYPE_MASK;
		switch (type) {
		case CREQ_BASE_TYPE_QP_EVENT:
			bnxt_qplib_process_qp_event
				(rcfw, (struct creq_qp_event *)creqe);
			rcfw->creq_qp_event_processed++;
			break;
		case CREQ_BASE_TYPE_FUNC_EVENT:
			if (!bnxt_qplib_process_func_event
			    (rcfw, (struct creq_func_event *)creqe))
				rcfw->creq_func_event_processed++;
			else
				dev_warn(&rcfw->pdev->dev,
					 "aeqe:%#x Not handled\n", type);
			break;
		default:
			if (type != ASYNC_EVENT_CMPL_TYPE_HWRM_ASYNC_EVENT)
				dev_warn(&rcfw->pdev->dev,
					 "creqe with event 0x%x not handled\n",
					 type);
			break;
		}
		raw_cons++;
		budget--;
	}

	if (creq->cons != raw_cons) {
		creq->cons = raw_cons;
		bnxt_qplib_ring_creq_db_rearm(rcfw->creq_bar_reg_iomem,
					      raw_cons, creq->max_elements,
					      rcfw->creq_ring_id, gen_p5);
	}
	spin_unlock_irqrestore(&creq->lock, flags);
}