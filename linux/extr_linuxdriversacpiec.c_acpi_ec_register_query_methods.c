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
typedef  int /*<<< orphan*/  u32 ;
struct acpi_ec {int dummy; } ;
struct acpi_buffer {int member_0; char* member_1; } ;
typedef  int /*<<< orphan*/  node_name ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SINGLE_NAME ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ec_add_query_handler (struct acpi_ec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_get_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_buffer*) ; 
 int sscanf (char*,char*,int*) ; 

__attribute__((used)) static acpi_status
acpi_ec_register_query_methods(acpi_handle handle, u32 level,
			       void *context, void **return_value)
{
	char node_name[5];
	struct acpi_buffer buffer = { sizeof(node_name), node_name };
	struct acpi_ec *ec = context;
	int value = 0;
	acpi_status status;

	status = acpi_get_name(handle, ACPI_SINGLE_NAME, &buffer);

	if (ACPI_SUCCESS(status) && sscanf(node_name, "_Q%x", &value) == 1)
		acpi_ec_add_query_handler(ec, value, handle, NULL, NULL);
	return AE_OK;
}