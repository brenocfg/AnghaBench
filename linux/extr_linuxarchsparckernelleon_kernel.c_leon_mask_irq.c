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
struct irq_data {scalar_t__ chip_data; } ;

/* Variables and functions */
 unsigned long LEON3_BYPASS_LOAD_PA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LEON3_BYPASS_STORE_PA (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  LEON_IMASK (int) ; 
 int irq_choose_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_data_get_affinity_mask (struct irq_data*) ; 
 int /*<<< orphan*/  leon_irq_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void leon_mask_irq(struct irq_data *data)
{
	unsigned long mask, oldmask, flags;
	int cpu;

	mask = (unsigned long)data->chip_data;
	cpu = irq_choose_cpu(irq_data_get_affinity_mask(data));
	spin_lock_irqsave(&leon_irq_lock, flags);
	oldmask = LEON3_BYPASS_LOAD_PA(LEON_IMASK(cpu));
	LEON3_BYPASS_STORE_PA(LEON_IMASK(cpu), (oldmask & ~mask));
	spin_unlock_irqrestore(&leon_irq_lock, flags);
}