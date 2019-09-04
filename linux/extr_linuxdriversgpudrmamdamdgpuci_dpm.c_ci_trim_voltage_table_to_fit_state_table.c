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
typedef  unsigned int u32 ;
struct atom_voltage_table {unsigned int count; int /*<<< orphan*/ * entries; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void ci_trim_voltage_table_to_fit_state_table(struct amdgpu_device *adev,
						     u32 max_voltage_steps,
						     struct atom_voltage_table *voltage_table)
{
	unsigned int i, diff;

	if (voltage_table->count <= max_voltage_steps)
		return;

	diff = voltage_table->count - max_voltage_steps;

	for (i = 0; i < max_voltage_steps; i++)
		voltage_table->entries[i] = voltage_table->entries[i + diff];

	voltage_table->count = max_voltage_steps;
}