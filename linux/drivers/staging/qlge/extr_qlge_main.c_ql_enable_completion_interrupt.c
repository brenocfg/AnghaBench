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
typedef  int u32 ;
struct ql_adapter {int /*<<< orphan*/  hw_lock; int /*<<< orphan*/  flags; struct intr_context* intr_context; } ;
struct intr_context {int /*<<< orphan*/  intr_en_mask; int /*<<< orphan*/  irq_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTR_EN ; 
 int /*<<< orphan*/  QL_MSIX_ENABLED ; 
 int /*<<< orphan*/  STS ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int ql_read32 (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_write32 (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

u32 ql_enable_completion_interrupt(struct ql_adapter *qdev, u32 intr)
{
	u32 var = 0;
	unsigned long hw_flags = 0;
	struct intr_context *ctx = qdev->intr_context + intr;

	if (likely(test_bit(QL_MSIX_ENABLED, &qdev->flags) && intr)) {
		/* Always enable if we're MSIX multi interrupts and
		 * it's not the default (zeroeth) interrupt.
		 */
		ql_write32(qdev, INTR_EN,
			   ctx->intr_en_mask);
		var = ql_read32(qdev, STS);
		return var;
	}

	spin_lock_irqsave(&qdev->hw_lock, hw_flags);
	if (atomic_dec_and_test(&ctx->irq_cnt)) {
		ql_write32(qdev, INTR_EN,
			   ctx->intr_en_mask);
		var = ql_read32(qdev, STS);
	}
	spin_unlock_irqrestore(&qdev->hw_lock, hw_flags);
	return var;
}