#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct creq_qp_event {int dummy; } ;
struct creq_func_event {int dummy; } ;
struct creq_base {scalar_t__ type; } ;
struct bnxt_qplib_hwq {scalar_t__ cons; int /*<<< orphan*/  lock; int /*<<< orphan*/  max_elements; scalar_t__ pbl_ptr; } ;
struct bnxt_qplib_rcfw {int /*<<< orphan*/  creq_bar_reg_iomem; TYPE_1__* pdev; int /*<<< orphan*/  creq_func_event_processed; int /*<<< orphan*/  creq_qp_event_processed; struct bnxt_qplib_hwq creq; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  CREQ_BASE_TYPE_FUNC_EVENT 129 
 scalar_t__ CREQ_BASE_TYPE_MASK ; 
#define  CREQ_BASE_TYPE_QP_EVENT 128 
 int /*<<< orphan*/  CREQ_CMP_VALID (struct creq_base*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CREQ_DB_REARM (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ CREQ_ENTRY_POLL_BUDGET ; 
 scalar_t__ HWQ_CMP (scalar_t__,struct bnxt_qplib_hwq*) ; 
 int /*<<< orphan*/  bnxt_qplib_process_func_event (struct bnxt_qplib_rcfw*,struct creq_func_event*) ; 
 int /*<<< orphan*/  bnxt_qplib_process_qp_event (struct bnxt_qplib_rcfw*,struct creq_qp_event*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 size_t get_creq_idx (scalar_t__) ; 
 size_t get_creq_pg (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void bnxt_qplib_service_creq(unsigned long data)
{
	struct bnxt_qplib_rcfw *rcfw = (struct bnxt_qplib_rcfw *)data;
	struct bnxt_qplib_hwq *creq = &rcfw->creq;
	struct creq_base *creqe, **creq_ptr;
	u32 sw_cons, raw_cons;
	unsigned long flags;
	u32 type, budget = CREQ_ENTRY_POLL_BUDGET;

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
				dev_warn
				(&rcfw->pdev->dev, "QPLIB:aeqe:%#x Not handled",
				 type);
			break;
		default:
			dev_warn(&rcfw->pdev->dev, "QPLIB: creqe with ");
			dev_warn(&rcfw->pdev->dev,
				 "QPLIB: op_event = 0x%x not handled", type);
			break;
		}
		raw_cons++;
		budget--;
	}

	if (creq->cons != raw_cons) {
		creq->cons = raw_cons;
		CREQ_DB_REARM(rcfw->creq_bar_reg_iomem, raw_cons,
			      creq->max_elements);
	}
	spin_unlock_irqrestore(&creq->lock, flags);
}