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
struct cyttsp4 {int /*<<< orphan*/  watchdog_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CY_WATCHDOG_TIMEOUT ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cyttsp4_start_wd_timer(struct cyttsp4 *cd)
{
	if (!CY_WATCHDOG_TIMEOUT)
		return;

	mod_timer(&cd->watchdog_timer, jiffies +
			msecs_to_jiffies(CY_WATCHDOG_TIMEOUT));
}