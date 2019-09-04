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
struct TYPE_2__ {int* offset; int* range; } ;
struct cxl_context {int pending_irq; int /*<<< orphan*/  wq; int /*<<< orphan*/  lock; int /*<<< orphan*/  irq_bitmap; int /*<<< orphan*/  pe; TYPE_1__ irqs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  int irq_hw_number_t ;
typedef  int __u16 ;

/* Variables and functions */
 int CXL_IRQ_RANGES ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  WARN (int,char*,...) ; 
 int /*<<< orphan*/  irq_get_irq_data (int) ; 
 int irqd_to_hwirq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_devel (char*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_cxl_afu_irq (struct cxl_context*,int,int,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t cxl_irq_afu(int irq, void *data)
{
	struct cxl_context *ctx = data;
	irq_hw_number_t hwirq = irqd_to_hwirq(irq_get_irq_data(irq));
	int irq_off, afu_irq = 0;
	__u16 range;
	int r;

	/*
	 * Look for the interrupt number.
	 * On bare-metal, we know range 0 only contains the PSL
	 * interrupt so we could start counting at range 1 and initialize
	 * afu_irq at 1.
	 * In a guest, range 0 also contains AFU interrupts, so it must
	 * be counted for. Therefore we initialize afu_irq at 0 to take into
	 * account the PSL interrupt.
	 *
	 * For code-readability, it just seems easier to go over all
	 * the ranges on bare-metal and guest. The end result is the same.
	 */
	for (r = 0; r < CXL_IRQ_RANGES; r++) {
		irq_off = hwirq - ctx->irqs.offset[r];
		range = ctx->irqs.range[r];
		if (irq_off >= 0 && irq_off < range) {
			afu_irq += irq_off;
			break;
		}
		afu_irq += range;
	}
	if (unlikely(r >= CXL_IRQ_RANGES)) {
		WARN(1, "Received AFU IRQ out of range for pe %i (virq %i hwirq %lx)\n",
		     ctx->pe, irq, hwirq);
		return IRQ_HANDLED;
	}

	trace_cxl_afu_irq(ctx, afu_irq, irq, hwirq);
	pr_devel("Received AFU interrupt %i for pe: %i (virq %i hwirq %lx)\n",
	       afu_irq, ctx->pe, irq, hwirq);

	if (unlikely(!ctx->irq_bitmap)) {
		WARN(1, "Received AFU IRQ for context with no IRQ bitmap\n");
		return IRQ_HANDLED;
	}
	spin_lock(&ctx->lock);
	set_bit(afu_irq - 1, ctx->irq_bitmap);
	ctx->pending_irq = true;
	spin_unlock(&ctx->lock);

	wake_up_all(&ctx->wq);

	return IRQ_HANDLED;
}