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
typedef  int /*<<< orphan*/  uint16_t ;
struct irq_desc {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIR_IRQ ; 
 int /*<<< orphan*/  MFIRINTREG ; 
 int /*<<< orphan*/  icu2_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct irq_desc* irq_to_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void vr41xx_disable_firint(uint16_t mask)
{
	struct irq_desc *desc = irq_to_desc(FIR_IRQ);
	unsigned long flags;

	raw_spin_lock_irqsave(&desc->lock, flags);
	icu2_clear(MFIRINTREG, mask);
	raw_spin_unlock_irqrestore(&desc->lock, flags);
}