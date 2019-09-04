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
struct irq_desc {int dummy; } ;
struct irq_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ BCSR_REG_INTSTAT ; 
 scalar_t__ __ffs (unsigned short) ; 
 unsigned short __raw_readw (scalar_t__) ; 
 scalar_t__ bcsr_csc_base ; 
 scalar_t__ bcsr_virt ; 
 int /*<<< orphan*/  chained_irq_enter (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  chained_irq_exit (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  generic_handle_irq (scalar_t__) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 

__attribute__((used)) static void bcsr_csc_handler(struct irq_desc *d)
{
	unsigned short bisr = __raw_readw(bcsr_virt + BCSR_REG_INTSTAT);
	struct irq_chip *chip = irq_desc_get_chip(d);

	chained_irq_enter(chip, d);
	generic_handle_irq(bcsr_csc_base + __ffs(bisr));
	chained_irq_exit(chip, d);
}