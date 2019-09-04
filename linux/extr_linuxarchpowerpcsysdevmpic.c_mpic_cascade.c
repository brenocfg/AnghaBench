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
struct mpic {int flags; } ;
struct irq_desc {int /*<<< orphan*/  irq_data; } ;
struct irq_chip {int /*<<< orphan*/  (* irq_eoi ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int MPIC_SECONDARY ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct mpic* irq_desc_get_handler_data (struct irq_desc*) ; 
 unsigned int mpic_get_one_irq (struct mpic*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mpic_cascade(struct irq_desc *desc)
{
	struct irq_chip *chip = irq_desc_get_chip(desc);
	struct mpic *mpic = irq_desc_get_handler_data(desc);
	unsigned int virq;

	BUG_ON(!(mpic->flags & MPIC_SECONDARY));

	virq = mpic_get_one_irq(mpic);
	if (virq)
		generic_handle_irq(virq);

	chip->irq_eoi(&desc->irq_data);
}