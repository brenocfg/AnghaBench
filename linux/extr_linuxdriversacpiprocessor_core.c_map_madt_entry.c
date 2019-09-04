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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {unsigned long length; } ;
struct acpi_table_madt {TYPE_1__ header; } ;
struct acpi_subtable_header {scalar_t__ type; scalar_t__ length; } ;
typedef  int /*<<< orphan*/  phys_cpuid_t ;

/* Variables and functions */
 scalar_t__ ACPI_MADT_TYPE_GENERIC_INTERRUPT ; 
 scalar_t__ ACPI_MADT_TYPE_LOCAL_APIC ; 
 scalar_t__ ACPI_MADT_TYPE_LOCAL_SAPIC ; 
 scalar_t__ ACPI_MADT_TYPE_LOCAL_X2APIC ; 
 int /*<<< orphan*/  PHYS_CPUID_INVALID ; 
 int /*<<< orphan*/  map_gicc_mpidr (struct acpi_subtable_header*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_lapic_id (struct acpi_subtable_header*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_lsapic_id (struct acpi_subtable_header*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_x2apic_id (struct acpi_subtable_header*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static phys_cpuid_t map_madt_entry(struct acpi_table_madt *madt,
				   int type, u32 acpi_id)
{
	unsigned long madt_end, entry;
	phys_cpuid_t phys_id = PHYS_CPUID_INVALID;	/* CPU hardware ID */

	if (!madt)
		return phys_id;

	entry = (unsigned long)madt;
	madt_end = entry + madt->header.length;

	/* Parse all entries looking for a match. */

	entry += sizeof(struct acpi_table_madt);
	while (entry + sizeof(struct acpi_subtable_header) < madt_end) {
		struct acpi_subtable_header *header =
			(struct acpi_subtable_header *)entry;
		if (header->type == ACPI_MADT_TYPE_LOCAL_APIC) {
			if (!map_lapic_id(header, acpi_id, &phys_id))
				break;
		} else if (header->type == ACPI_MADT_TYPE_LOCAL_X2APIC) {
			if (!map_x2apic_id(header, type, acpi_id, &phys_id))
				break;
		} else if (header->type == ACPI_MADT_TYPE_LOCAL_SAPIC) {
			if (!map_lsapic_id(header, type, acpi_id, &phys_id))
				break;
		} else if (header->type == ACPI_MADT_TYPE_GENERIC_INTERRUPT) {
			if (!map_gicc_mpidr(header, type, acpi_id, &phys_id))
				break;
		}
		entry += header->length;
	}
	return phys_id;
}