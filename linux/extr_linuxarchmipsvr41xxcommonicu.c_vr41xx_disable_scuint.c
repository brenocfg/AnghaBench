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
struct irq_desc {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ CPU_VR4122 ; 
 scalar_t__ CPU_VR4131 ; 
 scalar_t__ CPU_VR4133 ; 
 int /*<<< orphan*/  MSCUINTREG ; 
 int /*<<< orphan*/  SCU_IRQ ; 
 scalar_t__ current_cpu_type () ; 
 int /*<<< orphan*/  icu2_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct irq_desc* irq_to_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void vr41xx_disable_scuint(void)
{
	struct irq_desc *desc = irq_to_desc(SCU_IRQ);
	unsigned long flags;

	if (current_cpu_type() == CPU_VR4122 ||
	    current_cpu_type() == CPU_VR4131 ||
	    current_cpu_type() == CPU_VR4133) {
		raw_spin_lock_irqsave(&desc->lock, flags);
		icu2_write(MSCUINTREG, 0);
		raw_spin_unlock_irqrestore(&desc->lock, flags);
	}
}