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
typedef  scalar_t__ uint32_t ;
struct irq_source_info {scalar_t__ enable_reg; scalar_t__ status_reg; } ;
struct irq_service {int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_HPD_INT_CONTROL ; 
 int /*<<< orphan*/  DC_HPD_INT_POLARITY ; 
 int /*<<< orphan*/  DC_HPD_INT_STATUS ; 
 int /*<<< orphan*/  DC_HPD_SENSE_DELAYED ; 
 int /*<<< orphan*/  dal_irq_service_ack_generic (struct irq_service*,struct irq_source_info const*) ; 
 scalar_t__ dm_read_reg (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ get_reg_field_value (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_reg_field_value (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool hpd_ack(struct irq_service *irq_service,
		    const struct irq_source_info *info)
{
	uint32_t addr = info->status_reg;
	uint32_t value = dm_read_reg(irq_service->ctx, addr);
	uint32_t current_status = get_reg_field_value(value,
						      DC_HPD_INT_STATUS,
						      DC_HPD_SENSE_DELAYED);

	dal_irq_service_ack_generic(irq_service, info);

	value = dm_read_reg(irq_service->ctx, info->enable_reg);

	set_reg_field_value(value, current_status ? 0 : 1,
			    DC_HPD_INT_CONTROL,
			    DC_HPD_INT_POLARITY);

	dm_write_reg(irq_service->ctx, info->enable_reg, value);

	return true;
}