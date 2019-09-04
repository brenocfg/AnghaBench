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
typedef  int u64 ;

/* Variables and functions */
 unsigned int OCTEON_IRQ_MSI_BIT0 ; 
 int* msi_free_irq_bitmask ; 
 int /*<<< orphan*/  msi_free_irq_bitmask_lock ; 
 unsigned int msi_irq_size ; 
 unsigned long long* msi_multiple_irq_bitmask ; 
 int /*<<< orphan*/  panic (char*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void arch_teardown_msi_irq(unsigned int irq)
{
	int number_irqs;
	u64 bitmask;
	int index = 0;
	int irq0;

	if ((irq < OCTEON_IRQ_MSI_BIT0)
		|| (irq > msi_irq_size + OCTEON_IRQ_MSI_BIT0))
		panic("arch_teardown_msi_irq: Attempted to teardown illegal "
		      "MSI interrupt (%d)", irq);

	irq -= OCTEON_IRQ_MSI_BIT0;
	index = irq / 64;
	irq0 = irq % 64;

	/*
	 * Count the number of IRQs we need to free by looking at the
	 * msi_multiple_irq_bitmask. Each bit set means that the next
	 * IRQ is also owned by this device.
	 */
	number_irqs = 0;
	while ((irq0 + number_irqs < 64) &&
	       (msi_multiple_irq_bitmask[index]
		& (1ull << (irq0 + number_irqs))))
		number_irqs++;
	number_irqs++;
	/* Mask with one bit for each IRQ */
	bitmask = (1 << number_irqs) - 1;
	/* Shift the mask to the correct bit location */
	bitmask <<= irq0;
	if ((msi_free_irq_bitmask[index] & bitmask) != bitmask)
		panic("arch_teardown_msi_irq: Attempted to teardown MSI "
		      "interrupt (%d) not in use", irq);

	/* Checks are done, update the in use bitmask */
	spin_lock(&msi_free_irq_bitmask_lock);
	msi_free_irq_bitmask[index] &= ~bitmask;
	msi_multiple_irq_bitmask[index] &= ~bitmask;
	spin_unlock(&msi_free_irq_bitmask_lock);
}