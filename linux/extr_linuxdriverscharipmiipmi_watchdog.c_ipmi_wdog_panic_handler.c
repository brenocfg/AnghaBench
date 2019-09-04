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

/* Variables and functions */
 scalar_t__ WDOG_TIMEOUT_NONE ; 
 scalar_t__ ipmi_watchdog_state ; 
 int /*<<< orphan*/  panic_halt_ipmi_set_timeout () ; 
 int /*<<< orphan*/  panic_wdt_timeout ; 
 scalar_t__ pretimeout ; 
 int /*<<< orphan*/  timeout ; 
 scalar_t__ watchdog_user ; 

__attribute__((used)) static void ipmi_wdog_panic_handler(void *user_data)
{
	static int panic_event_handled;

	/*
	 * On a panic, if we have a panic timeout, make sure to extend
	 * the watchdog timer to a reasonable value to complete the
	 * panic, if the watchdog timer is running.  Plus the
	 * pretimeout is meaningless at panic time.
	 */
	if (watchdog_user && !panic_event_handled &&
	    ipmi_watchdog_state != WDOG_TIMEOUT_NONE) {
		/* Make sure we do this only once. */
		panic_event_handled = 1;

		timeout = panic_wdt_timeout;
		pretimeout = 0;
		panic_halt_ipmi_set_timeout();
	}
}