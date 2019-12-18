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
struct toshiba_acpi_dev {int /*<<< orphan*/  killswitch; int /*<<< orphan*/  wwan_rfk; } ;
struct rfkill {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rfkill_set_hw_state (int /*<<< orphan*/ ,int) ; 
 scalar_t__ toshiba_wireless_status (struct toshiba_acpi_dev*) ; 

__attribute__((used)) static void toshiba_acpi_wwan_poll(struct rfkill *rfkill, void *data)
{
	struct toshiba_acpi_dev *dev = data;

	if (toshiba_wireless_status(dev))
		return;

	rfkill_set_hw_state(dev->wwan_rfk, !dev->killswitch);
}