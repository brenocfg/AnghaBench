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
typedef  size_t u32 ;
struct its_vlpi_map {scalar_t__ vm; int /*<<< orphan*/  properties; } ;
struct TYPE_2__ {scalar_t__ vm; int /*<<< orphan*/  vlpi_lock; int /*<<< orphan*/  nr_vlpis; struct its_vlpi_map* vlpi_maps; int /*<<< orphan*/  nr_lpis; } ;
struct its_device {TYPE_1__ event_map; int /*<<< orphan*/  its; } ;
struct its_cmd_info {struct its_vlpi_map* map; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct its_device* irq_data_get_irq_chip_data (struct irq_data*) ; 
 scalar_t__ irqd_is_forwarded_to_vcpu (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_set_forwarded_to_vcpu (struct irq_data*) ; 
 size_t its_get_event_id (struct irq_data*) ; 
 int /*<<< orphan*/  its_map_vm (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  its_send_discard (struct its_device*,size_t) ; 
 int /*<<< orphan*/  its_send_vmapti (struct its_device*,size_t) ; 
 int /*<<< orphan*/  its_send_vmovi (struct its_device*,size_t) ; 
 struct its_vlpi_map* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpi_write_config (struct irq_data*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int its_vlpi_map(struct irq_data *d, struct its_cmd_info *info)
{
	struct its_device *its_dev = irq_data_get_irq_chip_data(d);
	u32 event = its_get_event_id(d);
	int ret = 0;

	if (!info->map)
		return -EINVAL;

	mutex_lock(&its_dev->event_map.vlpi_lock);

	if (!its_dev->event_map.vm) {
		struct its_vlpi_map *maps;

		maps = kcalloc(its_dev->event_map.nr_lpis, sizeof(*maps),
			       GFP_KERNEL);
		if (!maps) {
			ret = -ENOMEM;
			goto out;
		}

		its_dev->event_map.vm = info->map->vm;
		its_dev->event_map.vlpi_maps = maps;
	} else if (its_dev->event_map.vm != info->map->vm) {
		ret = -EINVAL;
		goto out;
	}

	/* Get our private copy of the mapping information */
	its_dev->event_map.vlpi_maps[event] = *info->map;

	if (irqd_is_forwarded_to_vcpu(d)) {
		/* Already mapped, move it around */
		its_send_vmovi(its_dev, event);
	} else {
		/* Ensure all the VPEs are mapped on this ITS */
		its_map_vm(its_dev->its, info->map->vm);

		/*
		 * Flag the interrupt as forwarded so that we can
		 * start poking the virtual property table.
		 */
		irqd_set_forwarded_to_vcpu(d);

		/* Write out the property to the prop table */
		lpi_write_config(d, 0xff, info->map->properties);

		/* Drop the physical mapping */
		its_send_discard(its_dev, event);

		/* and install the virtual one */
		its_send_vmapti(its_dev, event);

		/* Increment the number of VLPIs */
		its_dev->event_map.nr_vlpis++;
	}

out:
	mutex_unlock(&its_dev->event_map.vlpi_lock);
	return ret;
}