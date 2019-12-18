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
struct cros_ec_device {int /*<<< orphan*/  event_notifier; } ;
struct charger_data {int /*<<< orphan*/  notifier; struct cros_ec_device* ec_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  blocking_notifier_chain_unregister (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cros_usbpd_charger_unregister_notifier(void *data)
{
	struct charger_data *charger = data;
	struct cros_ec_device *ec_device = charger->ec_device;

	blocking_notifier_chain_unregister(&ec_device->event_notifier,
					   &charger->notifier);
}