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
typedef  int /*<<< orphan*/  u64 ;
struct ocxl_context {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  irq_idr; TYPE_2__* afu; int /*<<< orphan*/  pasid; } ;
struct afu_irq {scalar_t__ id; int /*<<< orphan*/  hw_irq; int /*<<< orphan*/  virq; int /*<<< orphan*/  trigger_page; } ;
struct TYPE_4__ {TYPE_1__* fn; } ;
struct TYPE_3__ {int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_IRQ_PER_CONTEXT ; 
 scalar_t__ idr_alloc (int /*<<< orphan*/ *,struct afu_irq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  irq_id_to_offset (struct ocxl_context*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct afu_irq*) ; 
 struct afu_irq* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocxl_link_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocxl_link_irq_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int setup_afu_irq (struct ocxl_context*,struct afu_irq*) ; 
 int /*<<< orphan*/  trace_ocxl_afu_irq_alloc (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ocxl_afu_irq_alloc(struct ocxl_context *ctx, u64 *irq_offset)
{
	struct afu_irq *irq;
	int rc;

	irq = kzalloc(sizeof(struct afu_irq), GFP_KERNEL);
	if (!irq)
		return -ENOMEM;

	/*
	 * We limit the number of afu irqs per context and per link to
	 * avoid a single process or user depleting the pool of IPIs
	 */

	mutex_lock(&ctx->irq_lock);

	irq->id = idr_alloc(&ctx->irq_idr, irq, 0, MAX_IRQ_PER_CONTEXT,
			GFP_KERNEL);
	if (irq->id < 0) {
		rc = -ENOSPC;
		goto err_unlock;
	}

	rc = ocxl_link_irq_alloc(ctx->afu->fn->link, &irq->hw_irq,
				&irq->trigger_page);
	if (rc)
		goto err_idr;

	rc = setup_afu_irq(ctx, irq);
	if (rc)
		goto err_alloc;

	*irq_offset = irq_id_to_offset(ctx, irq->id);

	trace_ocxl_afu_irq_alloc(ctx->pasid, irq->id, irq->virq, irq->hw_irq,
				*irq_offset);
	mutex_unlock(&ctx->irq_lock);
	return 0;

err_alloc:
	ocxl_link_free_irq(ctx->afu->fn->link, irq->hw_irq);
err_idr:
	idr_remove(&ctx->irq_idr, irq->id);
err_unlock:
	mutex_unlock(&ctx->irq_lock);
	kfree(irq);
	return rc;
}