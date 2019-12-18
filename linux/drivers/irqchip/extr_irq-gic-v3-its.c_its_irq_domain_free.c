#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct its_node {int /*<<< orphan*/  dev_alloc_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  col_map; int /*<<< orphan*/  nr_lpis; int /*<<< orphan*/  lpi_base; int /*<<< orphan*/  lpi_map; } ;
struct its_device {TYPE_1__ event_map; int /*<<< orphan*/  shared; struct its_node* its; } ;
struct irq_domain {int dummy; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ bitmap_empty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_count_order (unsigned int) ; 
 struct its_device* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_domain_free_irqs_parent (struct irq_domain*,unsigned int,unsigned int) ; 
 struct irq_data* irq_domain_get_irq_data (struct irq_domain*,unsigned int) ; 
 int /*<<< orphan*/  irq_domain_reset_irq_data (struct irq_data*) ; 
 int /*<<< orphan*/  its_free_device (struct its_device*) ; 
 int /*<<< orphan*/  its_get_event_id (struct irq_data*) ; 
 int /*<<< orphan*/  its_lpi_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_send_mapd (struct its_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void its_irq_domain_free(struct irq_domain *domain, unsigned int virq,
				unsigned int nr_irqs)
{
	struct irq_data *d = irq_domain_get_irq_data(domain, virq);
	struct its_device *its_dev = irq_data_get_irq_chip_data(d);
	struct its_node *its = its_dev->its;
	int i;

	bitmap_release_region(its_dev->event_map.lpi_map,
			      its_get_event_id(irq_domain_get_irq_data(domain, virq)),
			      get_count_order(nr_irqs));

	for (i = 0; i < nr_irqs; i++) {
		struct irq_data *data = irq_domain_get_irq_data(domain,
								virq + i);
		/* Nuke the entry in the domain */
		irq_domain_reset_irq_data(data);
	}

	mutex_lock(&its->dev_alloc_lock);

	/*
	 * If all interrupts have been freed, start mopping the
	 * floor. This is conditionned on the device not being shared.
	 */
	if (!its_dev->shared &&
	    bitmap_empty(its_dev->event_map.lpi_map,
			 its_dev->event_map.nr_lpis)) {
		its_lpi_free(its_dev->event_map.lpi_map,
			     its_dev->event_map.lpi_base,
			     its_dev->event_map.nr_lpis);
		kfree(its_dev->event_map.col_map);

		/* Unmap device/itt */
		its_send_mapd(its_dev, 0);
		its_free_device(its_dev);
	}

	mutex_unlock(&its->dev_alloc_lock);

	irq_domain_free_irqs_parent(domain, virq, nr_irqs);
}