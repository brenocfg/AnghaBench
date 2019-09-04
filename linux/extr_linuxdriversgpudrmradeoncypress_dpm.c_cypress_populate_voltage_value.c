#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct radeon_device {int dummy; } ;
struct atom_voltage_table {unsigned int count; TYPE_1__* entries; } ;
struct TYPE_5__ {int /*<<< orphan*/  value; scalar_t__ index; } ;
struct TYPE_4__ {scalar_t__ value; } ;
typedef  TYPE_2__ RV770_SMC_VOLTAGE_VALUE ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cpu_to_be16 (scalar_t__) ; 

__attribute__((used)) static int cypress_populate_voltage_value(struct radeon_device *rdev,
					  struct atom_voltage_table *table,
					  u16 value, RV770_SMC_VOLTAGE_VALUE *voltage)
{
	unsigned int i;

	for (i = 0; i < table->count; i++) {
		if (value <= table->entries[i].value) {
			voltage->index = (u8)i;
			voltage->value = cpu_to_be16(table->entries[i].value);
			break;
		}
	}

	if (i == table->count)
		return -EINVAL;

	return 0;
}