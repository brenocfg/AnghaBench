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
struct irq_data {unsigned int irq; } ;

/* Variables and functions */
 unsigned int MBOX_BITS_PER_CPU ; 
 unsigned int MIPS_IRQ_MBOX0 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 unsigned int get_ebase_cpunum () ; 
 scalar_t__ mips_irq_chip ; 
 scalar_t__ mips_irq_chip_reg_raw_w1c ; 

__attribute__((used)) static void irq_mbox_ack(struct irq_data *data)
{
	u32 mask;
	unsigned int mbox = data->irq - MIPS_IRQ_MBOX0;

	WARN_ON(mbox >= MBOX_BITS_PER_CPU);

	mask = 1 << (get_ebase_cpunum() * MBOX_BITS_PER_CPU + mbox);
	__raw_writel(mask, mips_irq_chip + mips_irq_chip_reg_raw_w1c + sizeof(u32));
}