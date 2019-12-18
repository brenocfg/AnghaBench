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
struct rmi_data {scalar_t__ rmi_irq; struct irq_domain* domain; } ;
struct irq_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_remove (struct irq_domain*) ; 
 int /*<<< orphan*/  irq_find_mapping (struct irq_domain*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rmi_irq_teardown(void *data)
{
	struct rmi_data *hdata = data;
	struct irq_domain *domain = hdata->domain;

	if (!domain)
		return;

	irq_dispose_mapping(irq_find_mapping(domain, 0));

	irq_domain_remove(domain);
	hdata->domain = NULL;
	hdata->rmi_irq = 0;
}