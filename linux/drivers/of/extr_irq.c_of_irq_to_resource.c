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
struct resource {int start; int end; int flags; char const* name; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int IORESOURCE_IRQ ; 
 int /*<<< orphan*/  irq_get_irq_data (int) ; 
 int irqd_get_trigger_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct resource*,int /*<<< orphan*/ ,int) ; 
 int of_irq_get (struct device_node*,int) ; 
 char const* of_node_full_name (struct device_node*) ; 
 int /*<<< orphan*/  of_property_read_string_index (struct device_node*,char*,int,char const**) ; 

int of_irq_to_resource(struct device_node *dev, int index, struct resource *r)
{
	int irq = of_irq_get(dev, index);

	if (irq < 0)
		return irq;

	/* Only dereference the resource if both the
	 * resource and the irq are valid. */
	if (r && irq) {
		const char *name = NULL;

		memset(r, 0, sizeof(*r));
		/*
		 * Get optional "interrupt-names" property to add a name
		 * to the resource.
		 */
		of_property_read_string_index(dev, "interrupt-names", index,
					      &name);

		r->start = r->end = irq;
		r->flags = IORESOURCE_IRQ | irqd_get_trigger_type(irq_get_irq_data(irq));
		r->name = name ? name : of_node_full_name(dev);
	}

	return irq;
}