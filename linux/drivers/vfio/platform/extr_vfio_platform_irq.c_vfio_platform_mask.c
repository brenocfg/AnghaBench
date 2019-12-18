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
struct vfio_platform_irq {int masked; int /*<<< orphan*/  lock; int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void vfio_platform_mask(struct vfio_platform_irq *irq_ctx)
{
	unsigned long flags;

	spin_lock_irqsave(&irq_ctx->lock, flags);

	if (!irq_ctx->masked) {
		disable_irq_nosync(irq_ctx->hwirq);
		irq_ctx->masked = true;
	}

	spin_unlock_irqrestore(&irq_ctx->lock, flags);
}