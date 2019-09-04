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
typedef  scalar_t__ u16 ;
struct atom_voltage_table {unsigned int count; TYPE_1__* entries; } ;
struct TYPE_2__ {scalar_t__ value; } ;

/* Variables and functions */

__attribute__((used)) static u16 btc_find_voltage(struct atom_voltage_table *table, u16 voltage)
{
	unsigned int i;

	for (i = 0; i < table->count; i++) {
		if (voltage <= table->entries[i].value)
			return table->entries[i].value;
	}

	return table->entries[table->count - 1].value;
}