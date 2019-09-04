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
struct octeon_irq_ciu_domain_data {unsigned int num_sum; } ;
struct irq_domain {struct octeon_irq_ciu_domain_data* host_data; } ;
typedef  int irq_hw_number_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  octeon_irq_chip_ciu_sum2 ; 
 int /*<<< orphan*/  octeon_irq_chip_ciu_sum2_edge ; 
 int /*<<< orphan*/ * octeon_irq_ciu_chip ; 
 int /*<<< orphan*/ * octeon_irq_ciu_chip_edge ; 
 scalar_t__ octeon_irq_ciu_is_edge (unsigned int,unsigned int) ; 
 scalar_t__** octeon_irq_ciu_to_irq ; 
 int octeon_irq_set_ciu_mapping (unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int octeon_irq_ciu_map(struct irq_domain *d,
			      unsigned int virq, irq_hw_number_t hw)
{
	int rv;
	unsigned int line = hw >> 6;
	unsigned int bit = hw & 63;
	struct octeon_irq_ciu_domain_data *dd = d->host_data;

	if (line >= dd->num_sum || octeon_irq_ciu_to_irq[line][bit] != 0)
		return -EINVAL;

	if (line == 2) {
		if (octeon_irq_ciu_is_edge(line, bit))
			rv = octeon_irq_set_ciu_mapping(virq, line, bit, 0,
				&octeon_irq_chip_ciu_sum2_edge,
				handle_edge_irq);
		else
			rv = octeon_irq_set_ciu_mapping(virq, line, bit, 0,
				&octeon_irq_chip_ciu_sum2,
				handle_level_irq);
	} else {
		if (octeon_irq_ciu_is_edge(line, bit))
			rv = octeon_irq_set_ciu_mapping(virq, line, bit, 0,
				octeon_irq_ciu_chip_edge,
				handle_edge_irq);
		else
			rv = octeon_irq_set_ciu_mapping(virq, line, bit, 0,
				octeon_irq_ciu_chip,
				handle_level_irq);
	}
	return rv;
}