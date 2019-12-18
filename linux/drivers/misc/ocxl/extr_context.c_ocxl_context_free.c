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
struct ocxl_context {TYPE_1__* afu; int /*<<< orphan*/  irq_idr; int /*<<< orphan*/  pasid; } ;
struct TYPE_2__ {int /*<<< orphan*/  contexts_lock; int /*<<< orphan*/  contexts_idr; int /*<<< orphan*/  pasid_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ocxl_context*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocxl_afu_irq_free_all (struct ocxl_context*) ; 
 int /*<<< orphan*/  ocxl_afu_put (TYPE_1__*) ; 

void ocxl_context_free(struct ocxl_context *ctx)
{
	mutex_lock(&ctx->afu->contexts_lock);
	ctx->afu->pasid_count--;
	idr_remove(&ctx->afu->contexts_idr, ctx->pasid);
	mutex_unlock(&ctx->afu->contexts_lock);

	ocxl_afu_irq_free_all(ctx);
	idr_destroy(&ctx->irq_idr);
	/* reference to the AFU taken in ocxl_context_init */
	ocxl_afu_put(ctx->afu);
	kfree(ctx);
}