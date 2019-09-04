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

/* Variables and functions */
 int /*<<< orphan*/  PIC_MASTER_CMD ; 
 int /*<<< orphan*/  PIC_SLAVE_CMD ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int i8259A_irq_real(unsigned int irq)
{
	int value;
	int irqmask = 1 << irq;

	if (irq < 8) {
		outb(0x0B, PIC_MASTER_CMD);	/* ISR register */
		value = inb(PIC_MASTER_CMD) & irqmask;
		outb(0x0A, PIC_MASTER_CMD);	/* back to the IRR register */
		return value;
	}
	outb(0x0B, PIC_SLAVE_CMD);	/* ISR register */
	value = inb(PIC_SLAVE_CMD) & (irqmask >> 8);
	outb(0x0A, PIC_SLAVE_CMD);	/* back to the IRR register */
	return value;
}