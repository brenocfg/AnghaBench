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
struct asus_wmi {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SYSTEM_NOTIFY ; 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_install_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct asus_wmi*) ; 
 int /*<<< orphan*/  asus_rfkill_notify ; 
 int /*<<< orphan*/  pr_warn (char*,char*) ; 

__attribute__((used)) static int asus_register_rfkill_notifier(struct asus_wmi *asus, char *node)
{
	acpi_status status;
	acpi_handle handle;

	status = acpi_get_handle(NULL, node, &handle);
	if (ACPI_FAILURE(status))
		return -ENODEV;

	status = acpi_install_notify_handler(handle, ACPI_SYSTEM_NOTIFY,
					     asus_rfkill_notify, asus);
	if (ACPI_FAILURE(status))
		pr_warn("Failed to register notify on %s\n", node);

	return 0;
}