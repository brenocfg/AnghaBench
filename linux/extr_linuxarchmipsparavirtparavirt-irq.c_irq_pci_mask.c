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
typedef  unsigned int u32 ;
struct irq_data {unsigned int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_writel (unsigned int,scalar_t__) ; 
 scalar_t__ mips_irq_chip ; 
 scalar_t__ mips_irq_chip_reg_en_w1c ; 

__attribute__((used)) static void irq_pci_mask(struct irq_data *data)
{
	u32 mask = 1u << data->irq;

	__raw_writel(mask, mips_irq_chip + mips_irq_chip_reg_en_w1c);
}