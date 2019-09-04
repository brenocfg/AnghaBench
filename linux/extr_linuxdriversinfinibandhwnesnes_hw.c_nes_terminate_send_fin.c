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
typedef  void* u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct nes_qp {int /*<<< orphan*/  lock; scalar_t__ last_aeq; void* hw_tcp_state; void* hw_iwarp_state; } ;
struct nes_hw_aeqe {int /*<<< orphan*/ * aeqe_words; } ;
struct nes_device {int dummy; } ;

/* Variables and functions */
 int NES_AEQE_IWARP_STATE_MASK ; 
 int NES_AEQE_IWARP_STATE_SHIFT ; 
 size_t NES_AEQE_MISC_IDX ; 
 int NES_AEQE_TCP_STATE_MASK ; 
 int NES_AEQE_TCP_STATE_SHIFT ; 
 int NES_CQP_QP_IWARP_STATE_TERMINATE ; 
 int NES_CQP_QP_TERM_DONT_SEND_TERM_MSG ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nes_hw_modify_qp (struct nes_device*,struct nes_qp*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void nes_terminate_send_fin(struct nes_device *nesdev,
			  struct nes_qp *nesqp, struct nes_hw_aeqe *aeqe)
{
	u32 aeq_info;
	u16 async_event_id;
	u8 tcp_state;
	u8 iwarp_state;
	unsigned long flags;

	aeq_info = le32_to_cpu(aeqe->aeqe_words[NES_AEQE_MISC_IDX]);
	tcp_state = (aeq_info & NES_AEQE_TCP_STATE_MASK) >> NES_AEQE_TCP_STATE_SHIFT;
	iwarp_state = (aeq_info & NES_AEQE_IWARP_STATE_MASK) >> NES_AEQE_IWARP_STATE_SHIFT;
	async_event_id = (u16)aeq_info;

	spin_lock_irqsave(&nesqp->lock, flags);
	nesqp->hw_iwarp_state = iwarp_state;
	nesqp->hw_tcp_state = tcp_state;
	nesqp->last_aeq = async_event_id;
	spin_unlock_irqrestore(&nesqp->lock, flags);

	/* Send the fin only */
	nes_hw_modify_qp(nesdev, nesqp, NES_CQP_QP_IWARP_STATE_TERMINATE |
		NES_CQP_QP_TERM_DONT_SEND_TERM_MSG, 0, 0);
}