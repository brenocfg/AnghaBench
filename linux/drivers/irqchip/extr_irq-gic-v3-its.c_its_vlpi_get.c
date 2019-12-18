#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_4__ {int /*<<< orphan*/  vlpi_lock; TYPE_1__* vlpi_maps; int /*<<< orphan*/  vm; } ;
struct its_device {TYPE_2__ event_map; } ;
struct its_cmd_info {TYPE_1__* map; } ;
struct irq_data {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 int EINVAL ; 
 struct its_device* irq_data_get_irq_chip_data (struct irq_data*) ; 
 size_t its_get_event_id (struct irq_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int its_vlpi_get(struct irq_data *d, struct its_cmd_info *info)
{
	struct its_device *its_dev = irq_data_get_irq_chip_data(d);
	u32 event = its_get_event_id(d);
	int ret = 0;

	mutex_lock(&its_dev->event_map.vlpi_lock);

	if (!its_dev->event_map.vm ||
	    !its_dev->event_map.vlpi_maps[event].vm) {
		ret = -EINVAL;
		goto out;
	}

	/* Copy our mapping information to the incoming request */
	*info->map = its_dev->event_map.vlpi_maps[event];

out:
	mutex_unlock(&its_dev->event_map.vlpi_lock);
	return ret;
}