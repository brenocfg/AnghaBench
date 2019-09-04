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
struct acpi_table_header {int oem_revision; int /*<<< orphan*/  oem_table_id; int /*<<< orphan*/  oem_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_OEM_ID_SIZE ; 
 int /*<<< orphan*/  ACPI_OEM_TABLE_ID_SIZE ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool qdf2400_erratum_44_present(struct acpi_table_header *h)
{
	if (memcmp(h->oem_id, "QCOM  ", ACPI_OEM_ID_SIZE))
		return false;

	if (!memcmp(h->oem_table_id, "QDF2432 ", ACPI_OEM_TABLE_ID_SIZE))
		return true;

	if (!memcmp(h->oem_table_id, "QDF2400 ", ACPI_OEM_TABLE_ID_SIZE) &&
			h->oem_revision == 1)
		return true;

	return false;
}