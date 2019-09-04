#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ space_id; int bit_width; int /*<<< orphan*/  address; } ;
struct lpit_residency_info {int frequency; TYPE_1__ gaddr; int /*<<< orphan*/  iomem_addr; } ;
struct acpi_lpit_native {int counter_frequency; TYPE_1__ residency_counter; } ;
struct TYPE_12__ {int flags; } ;
struct TYPE_11__ {TYPE_2__* dev_root; } ;
struct TYPE_10__ {int /*<<< orphan*/  attr; } ;
struct TYPE_9__ {int /*<<< orphan*/  attr; } ;
struct TYPE_8__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 scalar_t__ ACPI_ADR_SPACE_FIXED_HARDWARE ; 
 scalar_t__ ACPI_ADR_SPACE_SYSTEM_MEMORY ; 
 int ACPI_FADT_LOW_POWER_S0 ; 
 TYPE_6__ acpi_gbl_FADT ; 
 TYPE_5__ cpu_subsys ; 
 TYPE_4__ dev_attr_low_power_idle_cpu_residency_us ; 
 TYPE_3__ dev_attr_low_power_idle_system_residency_us ; 
 int /*<<< orphan*/  ioremap_nocache (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sysfs_add_file_to_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int tsc_khz ; 

__attribute__((used)) static void lpit_update_residency(struct lpit_residency_info *info,
				 struct acpi_lpit_native *lpit_native)
{
	info->frequency = lpit_native->counter_frequency ?
				lpit_native->counter_frequency : tsc_khz * 1000;
	if (!info->frequency)
		info->frequency = 1;

	info->gaddr = lpit_native->residency_counter;
	if (info->gaddr.space_id == ACPI_ADR_SPACE_SYSTEM_MEMORY) {
		info->iomem_addr = ioremap_nocache(info->gaddr.address,
						   info->gaddr.bit_width / 8);
		if (!info->iomem_addr)
			return;

		if (!(acpi_gbl_FADT.flags & ACPI_FADT_LOW_POWER_S0))
			return;

		/* Silently fail, if cpuidle attribute group is not present */
		sysfs_add_file_to_group(&cpu_subsys.dev_root->kobj,
					&dev_attr_low_power_idle_system_residency_us.attr,
					"cpuidle");
	} else if (info->gaddr.space_id == ACPI_ADR_SPACE_FIXED_HARDWARE) {
		if (!(acpi_gbl_FADT.flags & ACPI_FADT_LOW_POWER_S0))
			return;

		/* Silently fail, if cpuidle attribute group is not present */
		sysfs_add_file_to_group(&cpu_subsys.dev_root->kobj,
					&dev_attr_low_power_idle_cpu_residency_us.attr,
					"cpuidle");
	}
}