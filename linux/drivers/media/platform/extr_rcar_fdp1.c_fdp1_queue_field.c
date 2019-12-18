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
struct fdp1_field_buffer {int /*<<< orphan*/  list; } ;
struct fdp1_ctx {int /*<<< orphan*/  buffers_queued; TYPE_1__* fdp1; int /*<<< orphan*/  fields_queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  irqlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void fdp1_queue_field(struct fdp1_ctx *ctx,
			     struct fdp1_field_buffer *fbuf)
{
	unsigned long flags;

	spin_lock_irqsave(&ctx->fdp1->irqlock, flags);
	list_add_tail(&fbuf->list, &ctx->fields_queue);
	spin_unlock_irqrestore(&ctx->fdp1->irqlock, flags);

	ctx->buffers_queued++;
}