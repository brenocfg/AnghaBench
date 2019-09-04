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
struct dpu_hw_intr {int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  dpu_hw_intr_disable_irq_nolock (struct dpu_hw_intr*,int) ; 
 int /*<<< orphan*/  dpu_irq_map ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dpu_hw_intr_disable_irq(struct dpu_hw_intr *intr, int irq_idx)
{
	unsigned long irq_flags;

	if (!intr)
		return -EINVAL;

	if (irq_idx < 0 || irq_idx >= ARRAY_SIZE(dpu_irq_map)) {
		pr_err("invalid IRQ index: [%d]\n", irq_idx);
		return -EINVAL;
	}

	spin_lock_irqsave(&intr->irq_lock, irq_flags);
	dpu_hw_intr_disable_irq_nolock(intr, irq_idx);
	spin_unlock_irqrestore(&intr->irq_lock, irq_flags);

	return 0;
}