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
struct dpu_encoder_phys_cmd {int /*<<< orphan*/  pending_vblank_wq; int /*<<< orphan*/  pending_vblank_cnt; } ;
struct dpu_encoder_phys {int /*<<< orphan*/  parent; TYPE_1__* parent_ops; int /*<<< orphan*/  hw_pp; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* handle_vblank_virt ) (int /*<<< orphan*/ ,struct dpu_encoder_phys*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ATRACE_BEGIN (char*) ; 
 int /*<<< orphan*/  DPU_ATRACE_END (char*) ; 
 int /*<<< orphan*/  atomic_add_unless (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct dpu_encoder_phys*) ; 
 struct dpu_encoder_phys_cmd* to_dpu_encoder_phys_cmd (struct dpu_encoder_phys*) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dpu_encoder_phys_cmd_pp_rd_ptr_irq(void *arg, int irq_idx)
{
	struct dpu_encoder_phys *phys_enc = arg;
	struct dpu_encoder_phys_cmd *cmd_enc;

	if (!phys_enc || !phys_enc->hw_pp)
		return;

	DPU_ATRACE_BEGIN("rd_ptr_irq");
	cmd_enc = to_dpu_encoder_phys_cmd(phys_enc);

	if (phys_enc->parent_ops->handle_vblank_virt)
		phys_enc->parent_ops->handle_vblank_virt(phys_enc->parent,
			phys_enc);

	atomic_add_unless(&cmd_enc->pending_vblank_cnt, -1, 0);
	wake_up_all(&cmd_enc->pending_vblank_wq);
	DPU_ATRACE_END("rd_ptr_irq");
}