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
struct irq_data {int dummy; } ;
typedef  enum gic_intid_range { ____Placeholder_gic_intid_range } gic_intid_range ;

/* Variables and functions */
 int EPPI_RANGE ; 
 int PPI_RANGE ; 
 int get_intid_range (struct irq_data*) ; 

__attribute__((used)) static inline int gic_irq_in_rdist(struct irq_data *d)
{
	enum gic_intid_range range = get_intid_range(d);
	return range == PPI_RANGE || range == EPPI_RANGE;
}