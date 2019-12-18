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
struct tangox_irq_chip {scalar_t__ ctl; } ;
struct irq_domain {struct tangox_irq_chip* host_data; } ;
struct irq_desc {int dummy; } ;
struct irq_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ IRQ_CTL_HI ; 
 scalar_t__ IRQ_STATUS ; 
 int /*<<< orphan*/  chained_irq_enter (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  chained_irq_exit (struct irq_chip*,struct irq_desc*) ; 
 unsigned int intc_readl (struct tangox_irq_chip*,scalar_t__) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct irq_domain* irq_desc_get_handler_data (struct irq_desc*) ; 
 int /*<<< orphan*/  tangox_dispatch_irqs (struct irq_domain*,unsigned int,int) ; 

__attribute__((used)) static void tangox_irq_handler(struct irq_desc *desc)
{
	struct irq_domain *dom = irq_desc_get_handler_data(desc);
	struct irq_chip *host_chip = irq_desc_get_chip(desc);
	struct tangox_irq_chip *chip = dom->host_data;
	unsigned int status_lo, status_hi;

	chained_irq_enter(host_chip, desc);

	status_lo = intc_readl(chip, chip->ctl + IRQ_STATUS);
	status_hi = intc_readl(chip, chip->ctl + IRQ_CTL_HI + IRQ_STATUS);

	tangox_dispatch_irqs(dom, status_lo, 0);
	tangox_dispatch_irqs(dom, status_hi, 32);

	chained_irq_exit(host_chip, desc);
}