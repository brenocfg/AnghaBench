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
typedef  int /*<<< orphan*/  u32 ;
struct irq_fwspec {int param_count; int /*<<< orphan*/ * param; scalar_t__ fwnode; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  acpi_dev_get_irq_type (int,int) ; 
 scalar_t__ acpi_gsi_domain_id ; 
 int irq_create_fwspec_mapping (struct irq_fwspec*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

int acpi_register_gsi(struct device *dev, u32 gsi, int trigger,
		      int polarity)
{
	struct irq_fwspec fwspec;

	if (WARN_ON(!acpi_gsi_domain_id)) {
		pr_warn("GSI: No registered irqchip, giving up\n");
		return -EINVAL;
	}

	fwspec.fwnode = acpi_gsi_domain_id;
	fwspec.param[0] = gsi;
	fwspec.param[1] = acpi_dev_get_irq_type(trigger, polarity);
	fwspec.param_count = 2;

	return irq_create_fwspec_mapping(&fwspec);
}