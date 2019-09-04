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
struct acpi_namespace_node {int dummy; } ;
struct acpi_buffer {scalar_t__ pointer; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_LOCAL_BUFFER ; 
 int /*<<< orphan*/  ACPI_FREE (scalar_t__) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acpi_ns_handle_to_pathname (struct acpi_namespace_node*,struct acpi_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_printf (char*,...) ; 

void
acpi_ns_print_node_pathname(struct acpi_namespace_node *node,
			    const char *message)
{
	struct acpi_buffer buffer;
	acpi_status status;

	if (!node) {
		acpi_os_printf("[NULL NAME]");
		return;
	}

	/* Convert handle to full pathname and print it (with supplied message) */

	buffer.length = ACPI_ALLOCATE_LOCAL_BUFFER;

	status = acpi_ns_handle_to_pathname(node, &buffer, TRUE);
	if (ACPI_SUCCESS(status)) {
		if (message) {
			acpi_os_printf("%s ", message);
		}

		acpi_os_printf("%s", (char *)buffer.pointer);
		ACPI_FREE(buffer.pointer);
	}
}