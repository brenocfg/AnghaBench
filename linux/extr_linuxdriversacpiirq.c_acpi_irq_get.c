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
struct resource {int start; int end; unsigned long flags; } ;
struct irq_fwspec {int /*<<< orphan*/  fwnode; } ;
struct irq_domain {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAIN_BUS_ANY ; 
 int EINVAL ; 
 int EPROBE_DEFER ; 
 int acpi_irq_parse_one (int /*<<< orphan*/ ,unsigned int,struct irq_fwspec*,unsigned long*) ; 
 int irq_create_fwspec_mapping (struct irq_fwspec*) ; 
 struct irq_domain* irq_find_matching_fwnode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int acpi_irq_get(acpi_handle handle, unsigned int index, struct resource *res)
{
	struct irq_fwspec fwspec;
	struct irq_domain *domain;
	unsigned long flags;
	int rc;

	rc = acpi_irq_parse_one(handle, index, &fwspec, &flags);
	if (rc)
		return rc;

	domain = irq_find_matching_fwnode(fwspec.fwnode, DOMAIN_BUS_ANY);
	if (!domain)
		return -EPROBE_DEFER;

	rc = irq_create_fwspec_mapping(&fwspec);
	if (rc <= 0)
		return -EINVAL;

	res->start = rc;
	res->end = rc;
	res->flags = flags;

	return 0;
}