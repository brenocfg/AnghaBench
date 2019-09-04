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
struct spider_pic {int /*<<< orphan*/  host; scalar_t__ regs; } ;
struct irq_desc {int /*<<< orphan*/  irq_data; } ;
struct irq_chip {int /*<<< orphan*/  (* irq_eoi ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 unsigned int SPIDER_IRQ_INVALID ; 
 scalar_t__ TIR_CS ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 int in_be32 (scalar_t__) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct spider_pic* irq_desc_get_handler_data (struct irq_desc*) ; 
 unsigned int irq_linear_revmap (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spider_irq_cascade(struct irq_desc *desc)
{
	struct irq_chip *chip = irq_desc_get_chip(desc);
	struct spider_pic *pic = irq_desc_get_handler_data(desc);
	unsigned int cs, virq;

	cs = in_be32(pic->regs + TIR_CS) >> 24;
	if (cs == SPIDER_IRQ_INVALID)
		virq = 0;
	else
		virq = irq_linear_revmap(pic->host, cs);

	if (virq)
		generic_handle_irq(virq);

	chip->irq_eoi(&desc->irq_data);
}