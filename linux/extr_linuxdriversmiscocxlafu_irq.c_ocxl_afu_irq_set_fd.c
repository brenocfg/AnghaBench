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
typedef  int /*<<< orphan*/  u64 ;
struct ocxl_context {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  irq_idr; } ;
struct eventfd_ctx {int dummy; } ;
struct afu_irq {struct eventfd_ctx* ev_ctx; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct eventfd_ctx*) ; 
 struct eventfd_ctx* eventfd_ctx_fdget (int) ; 
 struct afu_irq* idr_find (int /*<<< orphan*/ *,int) ; 
 int irq_offset_to_id (struct ocxl_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ocxl_afu_irq_set_fd(struct ocxl_context *ctx, u64 irq_offset, int eventfd)
{
	struct afu_irq *irq;
	struct eventfd_ctx *ev_ctx;
	int rc = 0, id = irq_offset_to_id(ctx, irq_offset);

	mutex_lock(&ctx->irq_lock);
	irq = idr_find(&ctx->irq_idr, id);
	if (!irq) {
		rc = -EINVAL;
		goto unlock;
	}

	ev_ctx = eventfd_ctx_fdget(eventfd);
	if (IS_ERR(ev_ctx)) {
		rc = -EINVAL;
		goto unlock;
	}

	irq->ev_ctx = ev_ctx;
unlock:
	mutex_unlock(&ctx->irq_lock);
	return rc;
}