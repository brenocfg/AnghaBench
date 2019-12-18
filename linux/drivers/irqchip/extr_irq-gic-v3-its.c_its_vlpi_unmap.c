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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  vlpi_lock; int /*<<< orphan*/  vlpi_maps; int /*<<< orphan*/ * vm; int /*<<< orphan*/  nr_vlpis; } ;
struct its_device {TYPE_1__ event_map; int /*<<< orphan*/  its; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 int EINVAL ; 
 int LPI_PROP_DEFAULT_PRIO ; 
 int LPI_PROP_ENABLED ; 
 int LPI_PROP_GROUP1 ; 
 struct its_device* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_clr_forwarded_to_vcpu (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_is_forwarded_to_vcpu (struct irq_data*) ; 
 int /*<<< orphan*/  its_get_event_id (struct irq_data*) ; 
 int /*<<< orphan*/  its_send_discard (struct its_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_send_mapti (struct its_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_unmap_vm (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpi_update_config (struct irq_data*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int its_vlpi_unmap(struct irq_data *d)
{
	struct its_device *its_dev = irq_data_get_irq_chip_data(d);
	u32 event = its_get_event_id(d);
	int ret = 0;

	mutex_lock(&its_dev->event_map.vlpi_lock);

	if (!its_dev->event_map.vm || !irqd_is_forwarded_to_vcpu(d)) {
		ret = -EINVAL;
		goto out;
	}

	/* Drop the virtual mapping */
	its_send_discard(its_dev, event);

	/* and restore the physical one */
	irqd_clr_forwarded_to_vcpu(d);
	its_send_mapti(its_dev, d->hwirq, event);
	lpi_update_config(d, 0xff, (LPI_PROP_DEFAULT_PRIO |
				    LPI_PROP_ENABLED |
				    LPI_PROP_GROUP1));

	/* Potentially unmap the VM from this ITS */
	its_unmap_vm(its_dev->its, its_dev->event_map.vm);

	/*
	 * Drop the refcount and make the device available again if
	 * this was the last VLPI.
	 */
	if (!--its_dev->event_map.nr_vlpis) {
		its_dev->event_map.vm = NULL;
		kfree(its_dev->event_map.vlpi_maps);
	}

out:
	mutex_unlock(&its_dev->event_map.vlpi_lock);
	return ret;
}