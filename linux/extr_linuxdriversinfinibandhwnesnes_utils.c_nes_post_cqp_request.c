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
typedef  unsigned long u64 ;
typedef  size_t u32 ;
struct nes_hw_cqp_wqe {int /*<<< orphan*/ * wqe_words; } ;
struct TYPE_3__ {int sq_tail; int sq_size; int sq_head; int qp_id; int /*<<< orphan*/  lock; struct nes_hw_cqp_wqe* sq_vbase; } ;
struct nes_device {TYPE_1__ cqp; int /*<<< orphan*/  cqp_pending_reqs; scalar_t__ regs; } ;
struct TYPE_4__ {int /*<<< orphan*/ * wqe_words; } ;
struct nes_cqp_request {int /*<<< orphan*/  list; TYPE_2__ cqp_wqe; int /*<<< orphan*/  refcount; int /*<<< orphan*/  waiting; } ;

/* Variables and functions */
 size_t NES_CQP_DOWNLOAD_SEGMENT ; 
 size_t NES_CQP_OPCODE_MASK ; 
 int NES_CQP_WQE_COMP_CTX_LOW_IDX ; 
 int NES_CQP_WQE_DL_COMP_CTX_LOW_IDX ; 
 size_t NES_CQP_WQE_ID_IDX ; 
 size_t NES_CQP_WQE_OPCODE_IDX ; 
 int /*<<< orphan*/  NES_DBG_CQP ; 
 scalar_t__ NES_WQE_ALLOC ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  barrier () ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct nes_hw_cqp_wqe*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  nes_write32 (scalar_t__,int) ; 
 int /*<<< orphan*/  set_wqe_64bit_value (int /*<<< orphan*/ *,int,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void nes_post_cqp_request(struct nes_device *nesdev,
			  struct nes_cqp_request *cqp_request)
{
	struct nes_hw_cqp_wqe *cqp_wqe;
	unsigned long flags;
	u32 cqp_head;
	u64 u64temp;
	u32 opcode;
	int ctx_index = NES_CQP_WQE_COMP_CTX_LOW_IDX;

	spin_lock_irqsave(&nesdev->cqp.lock, flags);

	if (((((nesdev->cqp.sq_tail+(nesdev->cqp.sq_size*2))-nesdev->cqp.sq_head) &
			(nesdev->cqp.sq_size - 1)) != 1)
			&& (list_empty(&nesdev->cqp_pending_reqs))) {
		cqp_head = nesdev->cqp.sq_head++;
		nesdev->cqp.sq_head &= nesdev->cqp.sq_size-1;
		cqp_wqe = &nesdev->cqp.sq_vbase[cqp_head];
		memcpy(cqp_wqe, &cqp_request->cqp_wqe, sizeof(*cqp_wqe));
		opcode = le32_to_cpu(cqp_wqe->wqe_words[NES_CQP_WQE_OPCODE_IDX]);
		if ((opcode & NES_CQP_OPCODE_MASK) == NES_CQP_DOWNLOAD_SEGMENT)
			ctx_index = NES_CQP_WQE_DL_COMP_CTX_LOW_IDX;
		barrier();
		u64temp = (unsigned long)cqp_request;
		set_wqe_64bit_value(cqp_wqe->wqe_words, ctx_index, u64temp);
		nes_debug(NES_DBG_CQP, "CQP request (opcode 0x%02X), line 1 = 0x%08X put on CQPs SQ,"
			" request = %p, cqp_head = %u, cqp_tail = %u, cqp_size = %u,"
			" waiting = %d, refcount = %d.\n",
			opcode & NES_CQP_OPCODE_MASK,
			le32_to_cpu(cqp_wqe->wqe_words[NES_CQP_WQE_ID_IDX]), cqp_request,
			nesdev->cqp.sq_head, nesdev->cqp.sq_tail, nesdev->cqp.sq_size,
			cqp_request->waiting, atomic_read(&cqp_request->refcount));

		barrier();

		/* Ring doorbell (1 WQEs) */
		nes_write32(nesdev->regs+NES_WQE_ALLOC, 0x01800000 | nesdev->cqp.qp_id);

		barrier();
	} else {
		nes_debug(NES_DBG_CQP, "CQP request %p (opcode 0x%02X), line 1 = 0x%08X"
				" put on the pending queue.\n",
				cqp_request,
				le32_to_cpu(cqp_request->cqp_wqe.wqe_words[NES_CQP_WQE_OPCODE_IDX])&0x3f,
				le32_to_cpu(cqp_request->cqp_wqe.wqe_words[NES_CQP_WQE_ID_IDX]));
		list_add_tail(&cqp_request->list, &nesdev->cqp_pending_reqs);
	}

	spin_unlock_irqrestore(&nesdev->cqp.lock, flags);

	return;
}