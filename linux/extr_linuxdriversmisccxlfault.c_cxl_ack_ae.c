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
struct cxl_context {int pending_fault; int /*<<< orphan*/  wq; int /*<<< orphan*/  lock; int /*<<< orphan*/  dsisr; int /*<<< orphan*/  fault_dsisr; int /*<<< orphan*/  dar; int /*<<< orphan*/  fault_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ack_irq ) (struct cxl_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_PSL_TFC_An_AE ; 
 TYPE_1__* cxl_ops ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct cxl_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cxl_ack_ae(struct cxl_context *ctx)
{
	unsigned long flags;

	cxl_ops->ack_irq(ctx, CXL_PSL_TFC_An_AE, 0);

	spin_lock_irqsave(&ctx->lock, flags);
	ctx->pending_fault = true;
	ctx->fault_addr = ctx->dar;
	ctx->fault_dsisr = ctx->dsisr;
	spin_unlock_irqrestore(&ctx->lock, flags);

	wake_up_all(&ctx->wq);
}