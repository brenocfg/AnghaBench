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
struct acpi_ec {int reference_count; int /*<<< orphan*/  flags; int /*<<< orphan*/  gpe; int /*<<< orphan*/  handle; } ;
typedef  scalar_t__ acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ADR_SPACE_EC ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_GPE_EDGE_TRIGGERED ; 
 scalar_t__ ACPI_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_TYPE_METHOD ; 
 scalar_t__ AE_NOT_FOUND ; 
 int /*<<< orphan*/  EC_FLAGS_EC_HANDLER_INSTALLED ; 
 int /*<<< orphan*/  EC_FLAGS_EVT_HANDLER_INSTALLED ; 
 int /*<<< orphan*/  EC_FLAGS_GPE_HANDLER_INSTALLED ; 
 int /*<<< orphan*/  EC_FLAGS_STARTED ; 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_ec_enable_event (struct acpi_ec*) ; 
 int /*<<< orphan*/  acpi_ec_enable_gpe (struct acpi_ec*,int) ; 
 int /*<<< orphan*/  acpi_ec_enter_noirq (struct acpi_ec*) ; 
 int /*<<< orphan*/  acpi_ec_gpe_handler ; 
 int /*<<< orphan*/  acpi_ec_leave_noirq (struct acpi_ec*) ; 
 int /*<<< orphan*/  acpi_ec_register_query_methods ; 
 int /*<<< orphan*/  acpi_ec_space_handler ; 
 int /*<<< orphan*/  acpi_ec_start (struct acpi_ec*,int) ; 
 int /*<<< orphan*/  acpi_ec_stop (struct acpi_ec*,int) ; 
 scalar_t__ acpi_install_address_space_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct acpi_ec*) ; 
 scalar_t__ acpi_install_gpe_raw_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct acpi_ec*) ; 
 int /*<<< orphan*/  acpi_walk_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct acpi_ec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ec_install_handlers(struct acpi_ec *ec, bool handle_events)
{
	acpi_status status;

	acpi_ec_start(ec, false);

	if (!test_bit(EC_FLAGS_EC_HANDLER_INSTALLED, &ec->flags)) {
		acpi_ec_enter_noirq(ec);
		status = acpi_install_address_space_handler(ec->handle,
							    ACPI_ADR_SPACE_EC,
							    &acpi_ec_space_handler,
							    NULL, ec);
		if (ACPI_FAILURE(status)) {
			if (status == AE_NOT_FOUND) {
				/*
				 * Maybe OS fails in evaluating the _REG
				 * object. The AE_NOT_FOUND error will be
				 * ignored and OS * continue to initialize
				 * EC.
				 */
				pr_err("Fail in evaluating the _REG object"
					" of EC device. Broken bios is suspected.\n");
			} else {
				acpi_ec_stop(ec, false);
				return -ENODEV;
			}
		}
		set_bit(EC_FLAGS_EC_HANDLER_INSTALLED, &ec->flags);
	}

	if (!handle_events)
		return 0;

	if (!test_bit(EC_FLAGS_EVT_HANDLER_INSTALLED, &ec->flags)) {
		/* Find and register all query methods */
		acpi_walk_namespace(ACPI_TYPE_METHOD, ec->handle, 1,
				    acpi_ec_register_query_methods,
				    NULL, ec, NULL);
		set_bit(EC_FLAGS_EVT_HANDLER_INSTALLED, &ec->flags);
	}
	if (!test_bit(EC_FLAGS_GPE_HANDLER_INSTALLED, &ec->flags)) {
		status = acpi_install_gpe_raw_handler(NULL, ec->gpe,
					  ACPI_GPE_EDGE_TRIGGERED,
					  &acpi_ec_gpe_handler, ec);
		/* This is not fatal as we can poll EC events */
		if (ACPI_SUCCESS(status)) {
			set_bit(EC_FLAGS_GPE_HANDLER_INSTALLED, &ec->flags);
			acpi_ec_leave_noirq(ec);
			if (test_bit(EC_FLAGS_STARTED, &ec->flags) &&
			    ec->reference_count >= 1)
				acpi_ec_enable_gpe(ec, true);
		}
	}
	/* EC is fully operational, allow queries */
	acpi_ec_enable_event(ec);

	return 0;
}