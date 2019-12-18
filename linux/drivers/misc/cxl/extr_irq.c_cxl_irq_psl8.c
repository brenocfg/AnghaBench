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
typedef  int u64 ;
struct cxl_irq_info {int dsisr; int dar; int /*<<< orphan*/  afu_err; int /*<<< orphan*/  errstat; } ;
struct cxl_context {int pending_afu_err; int /*<<< orphan*/  wq; int /*<<< orphan*/  lock; int /*<<< orphan*/  afu_err; int /*<<< orphan*/  pe; TYPE_1__* afu; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* ack_irq ) (struct cxl_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* handle_psl_slice_error ) (struct cxl_context*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CXL_PSL_DSISR_An_A ; 
 int CXL_PSL_DSISR_An_AE ; 
 int CXL_PSL_DSISR_An_DM ; 
 int CXL_PSL_DSISR_An_DS ; 
 int CXL_PSL_DSISR_An_K ; 
 int CXL_PSL_DSISR_An_M ; 
 int CXL_PSL_DSISR_An_OC ; 
 int CXL_PSL_DSISR_An_P ; 
 int CXL_PSL_DSISR_An_PE ; 
 int CXL_PSL_DSISR_An_S ; 
 int CXL_PSL_DSISR_An_ST ; 
 int CXL_PSL_DSISR_An_UR ; 
 int /*<<< orphan*/  CXL_PSL_TFC_An_A ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 TYPE_2__* cxl_ops ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_devel (char*,...) ; 
 int /*<<< orphan*/  schedule_cxl_fault (struct cxl_context*,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct cxl_context*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct cxl_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_cxl_psl_irq (struct cxl_context*,int,int,int) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

irqreturn_t cxl_irq_psl8(int irq, struct cxl_context *ctx, struct cxl_irq_info *irq_info)
{
	u64 dsisr, dar;

	dsisr = irq_info->dsisr;
	dar = irq_info->dar;

	trace_cxl_psl_irq(ctx, irq, dsisr, dar);

	pr_devel("CXL interrupt %i for afu pe: %i DSISR: %#llx DAR: %#llx\n", irq, ctx->pe, dsisr, dar);

	if (dsisr & CXL_PSL_DSISR_An_DS) {
		/*
		 * We don't inherently need to sleep to handle this, but we do
		 * need to get a ref to the task's mm, which we can't do from
		 * irq context without the potential for a deadlock since it
		 * takes the task_lock. An alternate option would be to keep a
		 * reference to the task's mm the entire time it has cxl open,
		 * but to do that we need to solve the issue where we hold a
		 * ref to the mm, but the mm can hold a ref to the fd after an
		 * mmap preventing anything from being cleaned up.
		 */
		pr_devel("Scheduling segment miss handling for later pe: %i\n", ctx->pe);
		return schedule_cxl_fault(ctx, dsisr, dar);
	}

	if (dsisr & CXL_PSL_DSISR_An_M)
		pr_devel("CXL interrupt: PTE not found\n");
	if (dsisr & CXL_PSL_DSISR_An_P)
		pr_devel("CXL interrupt: Storage protection violation\n");
	if (dsisr & CXL_PSL_DSISR_An_A)
		pr_devel("CXL interrupt: AFU lock access to write through or cache inhibited storage\n");
	if (dsisr & CXL_PSL_DSISR_An_S)
		pr_devel("CXL interrupt: Access was afu_wr or afu_zero\n");
	if (dsisr & CXL_PSL_DSISR_An_K)
		pr_devel("CXL interrupt: Access not permitted by virtual page class key protection\n");

	if (dsisr & CXL_PSL_DSISR_An_DM) {
		/*
		 * In some cases we might be able to handle the fault
		 * immediately if hash_page would succeed, but we still need
		 * the task's mm, which as above we can't get without a lock
		 */
		pr_devel("Scheduling page fault handling for later pe: %i\n", ctx->pe);
		return schedule_cxl_fault(ctx, dsisr, dar);
	}
	if (dsisr & CXL_PSL_DSISR_An_ST)
		WARN(1, "CXL interrupt: Segment Table PTE not found\n");
	if (dsisr & CXL_PSL_DSISR_An_UR)
		pr_devel("CXL interrupt: AURP PTE not found\n");
	if (dsisr & CXL_PSL_DSISR_An_PE)
		return cxl_ops->handle_psl_slice_error(ctx, dsisr,
						irq_info->errstat);
	if (dsisr & CXL_PSL_DSISR_An_AE) {
		pr_devel("CXL interrupt: AFU Error 0x%016llx\n", irq_info->afu_err);

		if (ctx->pending_afu_err) {
			/*
			 * This shouldn't happen - the PSL treats these errors
			 * as fatal and will have reset the AFU, so there's not
			 * much point buffering multiple AFU errors.
			 * OTOH if we DO ever see a storm of these come in it's
			 * probably best that we log them somewhere:
			 */
			dev_err_ratelimited(&ctx->afu->dev, "CXL AFU Error "
					    "undelivered to pe %i: 0x%016llx\n",
					    ctx->pe, irq_info->afu_err);
		} else {
			spin_lock(&ctx->lock);
			ctx->afu_err = irq_info->afu_err;
			ctx->pending_afu_err = true;
			spin_unlock(&ctx->lock);

			wake_up_all(&ctx->wq);
		}

		cxl_ops->ack_irq(ctx, CXL_PSL_TFC_An_A, 0);
		return IRQ_HANDLED;
	}
	if (dsisr & CXL_PSL_DSISR_An_OC)
		pr_devel("CXL interrupt: OS Context Warning\n");

	WARN(1, "Unhandled CXL PSL IRQ\n");
	return IRQ_HANDLED;
}