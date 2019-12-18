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
struct dpu_encoder_phys_cmd {int dummy; } ;
struct dpu_encoder_phys {int /*<<< orphan*/  pending_kickoff_wq; int /*<<< orphan*/  pending_ctlstart_cnt; int /*<<< orphan*/  hw_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ATRACE_BEGIN (char*) ; 
 int /*<<< orphan*/  DPU_ATRACE_END (char*) ; 
 int /*<<< orphan*/  atomic_add_unless (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct dpu_encoder_phys_cmd* to_dpu_encoder_phys_cmd (struct dpu_encoder_phys*) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dpu_encoder_phys_cmd_ctl_start_irq(void *arg, int irq_idx)
{
	struct dpu_encoder_phys *phys_enc = arg;
	struct dpu_encoder_phys_cmd *cmd_enc;

	if (!phys_enc || !phys_enc->hw_ctl)
		return;

	DPU_ATRACE_BEGIN("ctl_start_irq");
	cmd_enc = to_dpu_encoder_phys_cmd(phys_enc);

	atomic_add_unless(&phys_enc->pending_ctlstart_cnt, -1, 0);

	/* Signal any waiting ctl start interrupt */
	wake_up_all(&phys_enc->pending_kickoff_wq);
	DPU_ATRACE_END("ctl_start_irq");
}