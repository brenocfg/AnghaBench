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
struct afu_irq {int /*<<< orphan*/  trigger_page; } ;

/* Variables and functions */
 struct afu_irq* idr_find (int /*<<< orphan*/ *,int) ; 
 int irq_offset_to_id (struct ocxl_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

u64 ocxl_afu_irq_get_addr(struct ocxl_context *ctx, u64 irq_offset)
{
	struct afu_irq *irq;
	int id = irq_offset_to_id(ctx, irq_offset);
	u64 addr = 0;

	mutex_lock(&ctx->irq_lock);
	irq = idr_find(&ctx->irq_idr, id);
	if (irq)
		addr = irq->trigger_page;
	mutex_unlock(&ctx->irq_lock);
	return addr;
}