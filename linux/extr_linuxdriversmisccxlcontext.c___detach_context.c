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
struct cxl_context {int status; int /*<<< orphan*/ * mm; TYPE_1__* afu; int /*<<< orphan*/  pid; int /*<<< orphan*/  fault_work; int /*<<< orphan*/  status_mutex; } ;
typedef  enum cxl_context_status { ____Placeholder_cxl_context_status } cxl_context_status ;
struct TYPE_4__ {int /*<<< orphan*/  (* irq_wait ) (struct cxl_context*) ;scalar_t__ (* link_ok ) (int /*<<< orphan*/ ,TYPE_1__*) ;scalar_t__ (* detach_process ) (struct cxl_context*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int CLOSED ; 
 int EBUSY ; 
 int STARTED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cxl_adapter_context_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxl_context_mm_count_put (struct cxl_context*) ; 
 int /*<<< orphan*/  cxl_ctx_put () ; 
 TYPE_2__* cxl_ops ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mm_context_remove_copro (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct cxl_context*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  stub3 (struct cxl_context*) ; 

int __detach_context(struct cxl_context *ctx)
{
	enum cxl_context_status status;

	mutex_lock(&ctx->status_mutex);
	status = ctx->status;
	ctx->status = CLOSED;
	mutex_unlock(&ctx->status_mutex);
	if (status != STARTED)
		return -EBUSY;

	/* Only warn if we detached while the link was OK.
	 * If detach fails when hw is down, we don't care.
	 */
	WARN_ON(cxl_ops->detach_process(ctx) &&
		cxl_ops->link_ok(ctx->afu->adapter, ctx->afu));
	flush_work(&ctx->fault_work); /* Only needed for dedicated process */

	/*
	 * Wait until no further interrupts are presented by the PSL
	 * for this context.
	 */
	if (cxl_ops->irq_wait)
		cxl_ops->irq_wait(ctx);

	/* release the reference to the group leader and mm handling pid */
	put_pid(ctx->pid);

	cxl_ctx_put();

	/* Decrease the attached context count on the adapter */
	cxl_adapter_context_put(ctx->afu->adapter);

	/* Decrease the mm count on the context */
	cxl_context_mm_count_put(ctx);
	if (ctx->mm)
		mm_context_remove_copro(ctx->mm);
	ctx->mm = NULL;

	return 0;
}