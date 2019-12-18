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
typedef  size_t u32 ;
struct radeon_device {int dummy; } ;
struct radeon_clock_voltage_dependency_table {size_t count; TYPE_1__* entries; } ;
struct TYPE_2__ {int /*<<< orphan*/  v; } ;

/* Variables and functions */
 int /*<<< orphan*/  ci_patch_with_vddci_leakage (struct radeon_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ci_patch_clock_voltage_dependency_table_with_vddci_leakage(struct radeon_device *rdev,
								       struct radeon_clock_voltage_dependency_table *table)
{
	u32 i;

	if (table) {
		for (i = 0; i < table->count; i++)
			ci_patch_with_vddci_leakage(rdev, &table->entries[i].v);
	}
}