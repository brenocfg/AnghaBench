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
struct msi_msg {int dummy; } ;
struct irq_data {struct intel_ir_data* chip_data; } ;
struct intel_ir_data {struct msi_msg msi_entry; } ;

/* Variables and functions */

__attribute__((used)) static void intel_ir_compose_msi_msg(struct irq_data *irq_data,
				     struct msi_msg *msg)
{
	struct intel_ir_data *ir_data = irq_data->chip_data;

	*msg = ir_data->msi_entry;
}