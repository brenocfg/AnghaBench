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
struct acpi_ec {int /*<<< orphan*/  work; int /*<<< orphan*/  nr_pending_queries; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EC_COMMAND_QUERY ; 
 int /*<<< orphan*/  EC_FLAGS_QUERY_PENDING ; 
 int /*<<< orphan*/  acpi_ec_cmd_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ec_event_enabled (struct acpi_ec*) ; 
 int /*<<< orphan*/  acpi_ec_mask_gpe (struct acpi_ec*) ; 
 int /*<<< orphan*/  ec_dbg_evt (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acpi_ec_submit_query(struct acpi_ec *ec)
{
	acpi_ec_mask_gpe(ec);
	if (!acpi_ec_event_enabled(ec))
		return;
	if (!test_and_set_bit(EC_FLAGS_QUERY_PENDING, &ec->flags)) {
		ec_dbg_evt("Command(%s) submitted/blocked",
			   acpi_ec_cmd_string(ACPI_EC_COMMAND_QUERY));
		ec->nr_pending_queries++;
		schedule_work(&ec->work);
	}
}