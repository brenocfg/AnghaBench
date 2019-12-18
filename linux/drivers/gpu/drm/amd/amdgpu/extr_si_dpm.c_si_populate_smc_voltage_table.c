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
struct atom_voltage_table {unsigned int count; TYPE_1__* entries; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * lowSMIO; } ;
struct TYPE_4__ {int /*<<< orphan*/  smio_low; } ;
typedef  TYPE_2__ SISLANDS_SMC_STATETABLE ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void si_populate_smc_voltage_table(struct amdgpu_device *adev,
					  const struct atom_voltage_table *voltage_table,
					  SISLANDS_SMC_STATETABLE *table)
{
	unsigned int i;

	for (i = 0; i < voltage_table->count; i++)
		table->lowSMIO[i] |= cpu_to_be32(voltage_table->entries[i].smio_low);
}