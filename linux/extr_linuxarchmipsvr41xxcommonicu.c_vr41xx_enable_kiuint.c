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
 scalar_t__ CPU_VR4111 ; 
 scalar_t__ CPU_VR4121 ; 
 int /*<<< orphan*/  KIU_IRQ ; 
 int /*<<< orphan*/  MKIUINTREG ; 
 scalar_t__ current_cpu_type () ; 
 int /*<<< orphan*/  icu1_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct irq_desc* irq_to_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void vr41xx_enable_kiuint(uint16_t mask)
{
	struct irq_desc *desc = irq_to_desc(KIU_IRQ);
	unsigned long flags;

	if (current_cpu_type() == CPU_VR4111 ||
	    current_cpu_type() == CPU_VR4121) {
		raw_spin_lock_irqsave(&desc->lock, flags);
		icu1_set(MKIUINTREG, mask);
		raw_spin_unlock_irqrestore(&desc->lock, flags);
	}
}