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
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_READ_METHOD ; 
 int /*<<< orphan*/  ACPI_DB_WRITE_METHOD ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ROOT_OBJECT ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  acpi_db_test_one_object ; 
 int /*<<< orphan*/  acpi_format_exception (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_install_method (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_walk_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_handle ; 
 int /*<<< orphan*/  read_method_code ; 
 int /*<<< orphan*/  write_handle ; 
 int /*<<< orphan*/  write_method_code ; 

__attribute__((used)) static void acpi_db_test_all_objects(void)
{
	acpi_status status;

	/* Install the debugger read-object control method if necessary */

	if (!read_handle) {
		status = acpi_install_method(read_method_code);
		if (ACPI_FAILURE(status)) {
			acpi_os_printf
			    ("%s, Could not install debugger read method\n",
			     acpi_format_exception(status));
			return;
		}

		status =
		    acpi_get_handle(NULL, ACPI_DB_READ_METHOD, &read_handle);
		if (ACPI_FAILURE(status)) {
			acpi_os_printf
			    ("Could not obtain handle for debug method %s\n",
			     ACPI_DB_READ_METHOD);
			return;
		}
	}

	/* Install the debugger write-object control method if necessary */

	if (!write_handle) {
		status = acpi_install_method(write_method_code);
		if (ACPI_FAILURE(status)) {
			acpi_os_printf
			    ("%s, Could not install debugger write method\n",
			     acpi_format_exception(status));
			return;
		}

		status =
		    acpi_get_handle(NULL, ACPI_DB_WRITE_METHOD, &write_handle);
		if (ACPI_FAILURE(status)) {
			acpi_os_printf
			    ("Could not obtain handle for debug method %s\n",
			     ACPI_DB_WRITE_METHOD);
			return;
		}
	}

	/* Walk the entire namespace, testing each supported named data object */

	(void)acpi_walk_namespace(ACPI_TYPE_ANY, ACPI_ROOT_OBJECT,
				  ACPI_UINT32_MAX, acpi_db_test_one_object,
				  NULL, NULL, NULL);
}