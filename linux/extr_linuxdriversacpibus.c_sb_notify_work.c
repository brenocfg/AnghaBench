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
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_OST_EC_OSPM_SHUTDOWN ; 
 int /*<<< orphan*/  ACPI_OST_SC_OS_SHUTDOWN_IN_PROGRESS ; 
 int /*<<< orphan*/  ACPI_SB_INDICATE_INTERVAL ; 
 int /*<<< orphan*/  acpi_evaluate_ost (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  orderly_poweroff (int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static void sb_notify_work(struct work_struct *dummy)
{
	acpi_handle sb_handle;

	orderly_poweroff(true);

	/*
	 * After initiating graceful shutdown, the ACPI spec requires OSPM
	 * to evaluate _OST method once every 10seconds to indicate that
	 * the shutdown is in progress
	 */
	acpi_get_handle(NULL, "\\_SB", &sb_handle);
	while (1) {
		pr_info("Graceful shutdown in progress.\n");
		acpi_evaluate_ost(sb_handle, ACPI_OST_EC_OSPM_SHUTDOWN,
				ACPI_OST_SC_OS_SHUTDOWN_IN_PROGRESS, NULL);
		msleep(ACPI_SB_INDICATE_INTERVAL);
	}
}