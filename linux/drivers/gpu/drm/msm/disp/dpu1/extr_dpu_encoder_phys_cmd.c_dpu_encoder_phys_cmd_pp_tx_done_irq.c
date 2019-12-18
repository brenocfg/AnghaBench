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
typedef  int /*<<< orphan*/  u32 ;
struct dpu_encoder_phys {int /*<<< orphan*/  pending_kickoff_wq; TYPE_2__* hw_pp; int /*<<< orphan*/  parent; int /*<<< orphan*/  enc_spinlock; int /*<<< orphan*/  pending_kickoff_cnt; TYPE_1__* parent_ops; } ;
struct TYPE_4__ {scalar_t__ idx; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* handle_frame_done ) (int /*<<< orphan*/ ,struct dpu_encoder_phys*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ATRACE_BEGIN (char*) ; 
 int /*<<< orphan*/  DPU_ATRACE_END (char*) ; 
 int /*<<< orphan*/  DPU_ENCODER_FRAME_EVENT_DONE ; 
 int /*<<< orphan*/  DRMID (int /*<<< orphan*/ ) ; 
 scalar_t__ PINGPONG_0 ; 
 int atomic_add_unless (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct dpu_encoder_phys*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_dpu_enc_phys_cmd_pp_tx_done (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dpu_encoder_phys_cmd_pp_tx_done_irq(void *arg, int irq_idx)
{
	struct dpu_encoder_phys *phys_enc = arg;
	unsigned long lock_flags;
	int new_cnt;
	u32 event = DPU_ENCODER_FRAME_EVENT_DONE;

	if (!phys_enc || !phys_enc->hw_pp)
		return;

	DPU_ATRACE_BEGIN("pp_done_irq");
	/* notify all synchronous clients first, then asynchronous clients */
	if (phys_enc->parent_ops->handle_frame_done)
		phys_enc->parent_ops->handle_frame_done(phys_enc->parent,
				phys_enc, event);

	spin_lock_irqsave(phys_enc->enc_spinlock, lock_flags);
	new_cnt = atomic_add_unless(&phys_enc->pending_kickoff_cnt, -1, 0);
	spin_unlock_irqrestore(phys_enc->enc_spinlock, lock_flags);

	trace_dpu_enc_phys_cmd_pp_tx_done(DRMID(phys_enc->parent),
					  phys_enc->hw_pp->idx - PINGPONG_0,
					  new_cnt, event);

	/* Signal any waiting atomic commit thread */
	wake_up_all(&phys_enc->pending_kickoff_wq);
	DPU_ATRACE_END("pp_done_irq");
}