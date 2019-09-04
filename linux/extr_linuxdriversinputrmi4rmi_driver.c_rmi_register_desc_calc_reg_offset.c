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
typedef  scalar_t__ u16 ;
struct rmi_register_descriptor {int num_registers; struct rmi_register_desc_item* registers; } ;
struct rmi_register_desc_item {scalar_t__ reg; } ;

/* Variables and functions */

int rmi_register_desc_calc_reg_offset(
		struct rmi_register_descriptor *rdesc, u16 reg)
{
	const struct rmi_register_desc_item *item;
	int offset = 0;
	int i;

	for (i = 0; i < rdesc->num_registers; i++) {
		item = &rdesc->registers[i];
		if (item->reg == reg)
			return offset;
		++offset;
	}
	return -1;
}