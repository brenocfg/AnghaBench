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
struct irq_desc {int /*<<< orphan*/  irq_data; } ;
struct irq_chip {int /*<<< orphan*/  (* irq_eoi ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 unsigned int irq_desc_get_irq (struct irq_desc*) ; 
 unsigned int socrates_fpga_pic_get_irq (unsigned int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void socrates_fpga_pic_cascade(struct irq_desc *desc)
{
	struct irq_chip *chip = irq_desc_get_chip(desc);
	unsigned int irq = irq_desc_get_irq(desc);
	unsigned int cascade_irq;

	/*
	 * See if we actually have an interrupt, call generic handling code if
	 * we do.
	 */
	cascade_irq = socrates_fpga_pic_get_irq(irq);

	if (cascade_irq)
		generic_handle_irq(cascade_irq);
	chip->irq_eoi(&desc->irq_data);
}