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
struct irq_domain {int bus_token; int /*<<< orphan*/  fwnode; } ;
struct device_node {int dummy; } ;
typedef  enum irq_domain_bus_token { ____Placeholder_irq_domain_bus_token } irq_domain_bus_token ;

/* Variables and functions */
#define  DOMAIN_BUS_IPI 128 
 struct device_node* to_of_node (int /*<<< orphan*/ ) ; 

int gic_ipi_domain_match(struct irq_domain *d, struct device_node *node,
			 enum irq_domain_bus_token bus_token)
{
	bool is_ipi;

	switch (bus_token) {
	case DOMAIN_BUS_IPI:
		is_ipi = d->bus_token == bus_token;
		return (!node || to_of_node(d->fwnode) == node) && is_ipi;
		break;
	default:
		return 0;
	}
}