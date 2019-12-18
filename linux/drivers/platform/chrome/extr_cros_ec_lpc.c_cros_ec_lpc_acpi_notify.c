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
typedef  scalar_t__ u32 ;
struct cros_ec_device {int /*<<< orphan*/  event_notifier; scalar_t__ mkbp_event_supported; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_NOTIFY_DEVICE_WAKE ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct cros_ec_device*) ; 
 scalar_t__ cros_ec_get_next_event (struct cros_ec_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_system_wakeup () ; 

__attribute__((used)) static void cros_ec_lpc_acpi_notify(acpi_handle device, u32 value, void *data)
{
	struct cros_ec_device *ec_dev = data;

	if (ec_dev->mkbp_event_supported &&
	    cros_ec_get_next_event(ec_dev, NULL) > 0)
		blocking_notifier_call_chain(&ec_dev->event_notifier, 0,
					     ec_dev);

	if (value == ACPI_NOTIFY_DEVICE_WAKE)
		pm_system_wakeup();
}