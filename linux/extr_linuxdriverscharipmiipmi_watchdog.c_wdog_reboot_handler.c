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
 int /*<<< orphan*/  IPMI_SET_TIMEOUT_NO_HB ; 
 int NOTIFY_OK ; 
 unsigned long SYS_HALT ; 
 unsigned long SYS_POWER_OFF ; 
 scalar_t__ WDOG_TIMEOUT_NONE ; 
 scalar_t__ WDOG_TIMEOUT_RESET ; 
 int /*<<< orphan*/  ipmi_set_timeout (int /*<<< orphan*/ ) ; 
 scalar_t__ ipmi_watchdog_state ; 
 scalar_t__ pretimeout ; 
 int timeout ; 
 scalar_t__ watchdog_user ; 

__attribute__((used)) static int wdog_reboot_handler(struct notifier_block *this,
			       unsigned long         code,
			       void                  *unused)
{
	static int reboot_event_handled;

	if ((watchdog_user) && (!reboot_event_handled)) {
		/* Make sure we only do this once. */
		reboot_event_handled = 1;

		if (code == SYS_POWER_OFF || code == SYS_HALT) {
			/* Disable the WDT if we are shutting down. */
			ipmi_watchdog_state = WDOG_TIMEOUT_NONE;
			ipmi_set_timeout(IPMI_SET_TIMEOUT_NO_HB);
		} else if (ipmi_watchdog_state != WDOG_TIMEOUT_NONE) {
			/* Set a long timer to let the reboot happen or
			   reset if it hangs, but only if the watchdog
			   timer was already running. */
			if (timeout < 120)
				timeout = 120;
			pretimeout = 0;
			ipmi_watchdog_state = WDOG_TIMEOUT_RESET;
			ipmi_set_timeout(IPMI_SET_TIMEOUT_NO_HB);
		}
	}
	return NOTIFY_OK;
}