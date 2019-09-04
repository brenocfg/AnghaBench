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
typedef  unsigned int u32 ;
struct octeon_irq_ciu_domain_data {unsigned int num_sum; } ;
struct irq_domain {struct octeon_irq_ciu_domain_data* host_data; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int octeon_irq_ciu_xlat(struct irq_domain *d,
			       struct device_node *node,
			       const u32 *intspec,
			       unsigned int intsize,
			       unsigned long *out_hwirq,
			       unsigned int *out_type)
{
	unsigned int ciu, bit;
	struct octeon_irq_ciu_domain_data *dd = d->host_data;

	ciu = intspec[0];
	bit = intspec[1];

	if (ciu >= dd->num_sum || bit > 63)
		return -EINVAL;

	*out_hwirq = (ciu << 6) | bit;
	*out_type = 0;

	return 0;
}