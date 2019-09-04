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
struct TYPE_2__ {int /*<<< orphan*/  vm; } ;
struct its_device {TYPE_1__ event_map; } ;
struct its_cmd_info {scalar_t__ cmd_type; int config; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int LPI_PROP_ENABLED ; 
 scalar_t__ PROP_UPDATE_AND_INV_VLPI ; 
 struct its_device* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_is_forwarded_to_vcpu (struct irq_data*) ; 
 int /*<<< orphan*/  its_vlpi_set_doorbell (struct irq_data*,int) ; 
 int /*<<< orphan*/  lpi_update_config (struct irq_data*,int,int) ; 
 int /*<<< orphan*/  lpi_write_config (struct irq_data*,int,int) ; 

__attribute__((used)) static int its_vlpi_prop_update(struct irq_data *d, struct its_cmd_info *info)
{
	struct its_device *its_dev = irq_data_get_irq_chip_data(d);

	if (!its_dev->event_map.vm || !irqd_is_forwarded_to_vcpu(d))
		return -EINVAL;

	if (info->cmd_type == PROP_UPDATE_AND_INV_VLPI)
		lpi_update_config(d, 0xff, info->config);
	else
		lpi_write_config(d, 0xff, info->config);
	its_vlpi_set_doorbell(d, !!(info->config & LPI_PROP_ENABLED));

	return 0;
}