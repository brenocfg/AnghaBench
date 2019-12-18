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
struct irq_domain {int dummy; } ;
struct irq_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 struct irq_domain* irq_desc_get_handler_data (struct irq_desc*) ; 
 unsigned int irq_desc_get_irq (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_find_mapping (struct irq_domain*,unsigned int) ; 

__attribute__((used)) static void tb10x_irq_cascade(struct irq_desc *desc)
{
	struct irq_domain *domain = irq_desc_get_handler_data(desc);
	unsigned int irq = irq_desc_get_irq(desc);

	generic_handle_irq(irq_find_mapping(domain, irq));
}