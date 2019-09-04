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

/* Variables and functions */
 int /*<<< orphan*/  irq_domain_reset_irq_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_get_irq_data (unsigned int) ; 

__attribute__((used)) static void combiner_irq_unmap(struct irq_domain *domain, unsigned int irq)
{
	irq_domain_reset_irq_data(irq_get_irq_data(irq));
}