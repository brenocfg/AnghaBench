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
struct acpi_table_header {scalar_t__ oem_revision; int /*<<< orphan*/  oem_table_id; int /*<<< orphan*/  oem_id; } ;
struct acpi_platform_list {scalar_t__ pred; scalar_t__ oem_revision; scalar_t__* oem_table_id; scalar_t__* oem_id; int /*<<< orphan*/  table; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_OEM_ID_SIZE ; 
 int /*<<< orphan*/  ACPI_OEM_TABLE_ID_SIZE ; 
 int ENODEV ; 
 scalar_t__ acpi_disabled ; 
 int /*<<< orphan*/  acpi_get_table_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_table_header*) ; 
 scalar_t__ all_versions ; 
 scalar_t__ equal ; 
 scalar_t__ greater_than_or_equal ; 
 scalar_t__ less_than_or_equal ; 
 scalar_t__ strncmp (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int acpi_match_platform_list(const struct acpi_platform_list *plat)
{
	struct acpi_table_header hdr;
	int idx = 0;

	if (acpi_disabled)
		return -ENODEV;

	for (; plat->oem_id[0]; plat++, idx++) {
		if (ACPI_FAILURE(acpi_get_table_header(plat->table, 0, &hdr)))
			continue;

		if (strncmp(plat->oem_id, hdr.oem_id, ACPI_OEM_ID_SIZE))
			continue;

		if (strncmp(plat->oem_table_id, hdr.oem_table_id, ACPI_OEM_TABLE_ID_SIZE))
			continue;

		if ((plat->pred == all_versions) ||
		    (plat->pred == less_than_or_equal && hdr.oem_revision <= plat->oem_revision) ||
		    (plat->pred == greater_than_or_equal && hdr.oem_revision >= plat->oem_revision) ||
		    (plat->pred == equal && hdr.oem_revision == plat->oem_revision))
			return idx;
	}

	return -ENODEV;
}