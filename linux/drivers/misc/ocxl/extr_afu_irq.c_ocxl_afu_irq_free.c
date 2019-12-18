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
struct ocxl_context {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  irq_idr; } ;
struct afu_irq {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  afu_irq_free (struct afu_irq*,struct ocxl_context*) ; 
 struct afu_irq* idr_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ocxl_afu_irq_free(struct ocxl_context *ctx, int irq_id)
{
	struct afu_irq *irq;

	mutex_lock(&ctx->irq_lock);

	irq = idr_find(&ctx->irq_idr, irq_id);
	if (!irq) {
		mutex_unlock(&ctx->irq_lock);
		return -EINVAL;
	}
	idr_remove(&ctx->irq_idr, irq->id);
	afu_irq_free(irq, ctx);
	mutex_unlock(&ctx->irq_lock);
	return 0;
}