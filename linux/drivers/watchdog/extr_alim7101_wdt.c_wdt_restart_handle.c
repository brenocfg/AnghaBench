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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  WDT_ENABLE ; 
 int /*<<< orphan*/  wdt_change (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wdt_restart_handle(struct notifier_block *this, unsigned long mode,
			      void *cmd)
{
	/*
	 * Cobalt devices have no way of rebooting themselves other
	 * than getting the watchdog to pull reset, so we restart the
	 * watchdog on reboot with no heartbeat.
	 */
	wdt_change(WDT_ENABLE);

	/* loop until the watchdog fires */
	while (true)
		;

	return NOTIFY_DONE;
}