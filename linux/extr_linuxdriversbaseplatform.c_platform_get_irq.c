#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int flags; int start; } ;
struct TYPE_3__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_HANDLE (TYPE_1__*) ; 
 int /*<<< orphan*/  CONFIG_OF_IRQ ; 
 int ENXIO ; 
 int EPROBE_DEFER ; 
 int IORESOURCE_BITS ; 
 int IORESOURCE_DISABLED ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int acpi_irq_get (int /*<<< orphan*/ ,unsigned int,struct resource*) ; 
 scalar_t__ has_acpi_companion (TYPE_1__*) ; 
 struct irq_data* irq_get_irq_data (int) ; 
 int /*<<< orphan*/  irqd_set_trigger_type (struct irq_data*,int) ; 
 int of_irq_get (scalar_t__,unsigned int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,unsigned int) ; 

int platform_get_irq(struct platform_device *dev, unsigned int num)
{
#ifdef CONFIG_SPARC
	/* sparc does not have irqs represented as IORESOURCE_IRQ resources */
	if (!dev || num >= dev->archdata.num_irqs)
		return -ENXIO;
	return dev->archdata.irqs[num];
#else
	struct resource *r;
	if (IS_ENABLED(CONFIG_OF_IRQ) && dev->dev.of_node) {
		int ret;

		ret = of_irq_get(dev->dev.of_node, num);
		if (ret > 0 || ret == -EPROBE_DEFER)
			return ret;
	}

	r = platform_get_resource(dev, IORESOURCE_IRQ, num);
	if (has_acpi_companion(&dev->dev)) {
		if (r && r->flags & IORESOURCE_DISABLED) {
			int ret;

			ret = acpi_irq_get(ACPI_HANDLE(&dev->dev), num, r);
			if (ret)
				return ret;
		}
	}

	/*
	 * The resources may pass trigger flags to the irqs that need
	 * to be set up. It so happens that the trigger flags for
	 * IORESOURCE_BITS correspond 1-to-1 to the IRQF_TRIGGER*
	 * settings.
	 */
	if (r && r->flags & IORESOURCE_BITS) {
		struct irq_data *irqd;

		irqd = irq_get_irq_data(r->start);
		if (!irqd)
			return -ENXIO;
		irqd_set_trigger_type(irqd, r->flags & IORESOURCE_BITS);
	}

	return r ? r->start : -ENXIO;
#endif
}