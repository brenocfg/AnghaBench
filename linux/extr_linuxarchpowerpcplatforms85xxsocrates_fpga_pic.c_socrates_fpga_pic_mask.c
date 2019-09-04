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
typedef  int u32 ;
struct irq_data {int dummy; } ;
struct TYPE_2__ {int irq_line; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPGA_PIC_IRQMASK (int) ; 
 int SOCRATES_FPGA_IRQ_MASK ; 
 TYPE_1__* fpga_irqs ; 
 unsigned int irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  socrates_fpga_pic_lock ; 
 int socrates_fpga_pic_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socrates_fpga_pic_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void socrates_fpga_pic_mask(struct irq_data *d)
{
	unsigned long flags;
	unsigned int hwirq = irqd_to_hwirq(d);
	int irq_line;
	u32 mask;

	irq_line = fpga_irqs[hwirq].irq_line;
	raw_spin_lock_irqsave(&socrates_fpga_pic_lock, flags);
	mask = socrates_fpga_pic_read(FPGA_PIC_IRQMASK(irq_line))
		& SOCRATES_FPGA_IRQ_MASK;
	mask &= ~(1 << hwirq);
	socrates_fpga_pic_write(FPGA_PIC_IRQMASK(irq_line), mask);
	raw_spin_unlock_irqrestore(&socrates_fpga_pic_lock, flags);
}