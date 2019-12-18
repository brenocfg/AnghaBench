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
struct its_device {TYPE_1__* its; } ;
struct its_cmd_info {int cmd_type; } ;
struct irq_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  is_v4; } ;

/* Variables and functions */
 int EINVAL ; 
#define  GET_VLPI 131 
#define  MAP_VLPI 130 
#define  PROP_UPDATE_AND_INV_VLPI 129 
#define  PROP_UPDATE_VLPI 128 
 struct its_device* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int its_vlpi_get (struct irq_data*,struct its_cmd_info*) ; 
 int its_vlpi_map (struct irq_data*,struct its_cmd_info*) ; 
 int its_vlpi_prop_update (struct irq_data*,struct its_cmd_info*) ; 
 int its_vlpi_unmap (struct irq_data*) ; 

__attribute__((used)) static int its_irq_set_vcpu_affinity(struct irq_data *d, void *vcpu_info)
{
	struct its_device *its_dev = irq_data_get_irq_chip_data(d);
	struct its_cmd_info *info = vcpu_info;

	/* Need a v4 ITS */
	if (!its_dev->its->is_v4)
		return -EINVAL;

	/* Unmap request? */
	if (!info)
		return its_vlpi_unmap(d);

	switch (info->cmd_type) {
	case MAP_VLPI:
		return its_vlpi_map(d, info);

	case GET_VLPI:
		return its_vlpi_get(d, info);

	case PROP_UPDATE_VLPI:
	case PROP_UPDATE_AND_INV_VLPI:
		return its_vlpi_prop_update(d, info);

	default:
		return -EINVAL;
	}
}