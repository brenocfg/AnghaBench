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
struct radeon_device {int dummy; } ;
struct radeon_clock_voltage_dependency_table {size_t count; TYPE_1__* entries; } ;
struct atom_voltage_table {size_t count; TYPE_2__* entries; scalar_t__ phase_delay; scalar_t__ mask_low; } ;
struct TYPE_4__ {scalar_t__ smio_low; int /*<<< orphan*/  value; } ;
struct TYPE_3__ {int /*<<< orphan*/  v; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int si_get_svi2_voltage_table(struct radeon_device *rdev,
				     struct radeon_clock_voltage_dependency_table *voltage_dependency_table,
				     struct atom_voltage_table *voltage_table)
{
	u32 i;

	if (voltage_dependency_table == NULL)
		return -EINVAL;

	voltage_table->mask_low = 0;
	voltage_table->phase_delay = 0;

	voltage_table->count = voltage_dependency_table->count;
	for (i = 0; i < voltage_table->count; i++) {
		voltage_table->entries[i].value = voltage_dependency_table->entries[i].v;
		voltage_table->entries[i].smio_low = 0;
	}

	return 0;
}