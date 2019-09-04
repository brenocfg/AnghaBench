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
typedef  union acpi_object {int dummy; } acpi_object ;
struct acpi_buffer {int /*<<< orphan*/  pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,struct acpi_buffer*) ; 
 union acpi_object* pkg_to_buf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static union acpi_object *acpi_label_info(acpi_handle handle)
{
	acpi_status rc;
	struct acpi_buffer buf = { ACPI_ALLOCATE_BUFFER, NULL };

	rc = acpi_evaluate_object(handle, "_LSI", NULL, &buf);
	if (ACPI_FAILURE(rc))
		return NULL;
	return pkg_to_buf(buf.pointer);
}