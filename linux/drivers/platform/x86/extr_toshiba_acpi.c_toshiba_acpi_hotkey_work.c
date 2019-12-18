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
struct work_struct {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ec_get_handle () ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void toshiba_acpi_hotkey_work(struct work_struct *work)
{
	acpi_handle ec_handle = ec_get_handle();
	acpi_status status;

	if (!ec_handle)
		return;

	status = acpi_evaluate_object(ec_handle, "NTFY", NULL, NULL);
	if (ACPI_FAILURE(status))
		pr_err("ACPI NTFY method execution failed\n");
}