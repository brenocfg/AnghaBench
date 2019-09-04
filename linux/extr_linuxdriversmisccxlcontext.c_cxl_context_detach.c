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
struct cxl_context {int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int __detach_context (struct cxl_context*) ; 
 int /*<<< orphan*/  afu_release_irqs (struct cxl_context*,struct cxl_context*) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

void cxl_context_detach(struct cxl_context *ctx)
{
	int rc;

	rc = __detach_context(ctx);
	if (rc)
		return;

	afu_release_irqs(ctx, ctx);
	wake_up_all(&ctx->wq);
}