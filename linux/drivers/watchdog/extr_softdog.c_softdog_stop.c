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
struct watchdog_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SOFT_WATCHDOG_PRETIMEOUT ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  softdog_preticktock ; 
 int /*<<< orphan*/  softdog_ticktock ; 

__attribute__((used)) static int softdog_stop(struct watchdog_device *w)
{
	if (hrtimer_cancel(&softdog_ticktock))
		module_put(THIS_MODULE);

	if (IS_ENABLED(CONFIG_SOFT_WATCHDOG_PRETIMEOUT))
		hrtimer_cancel(&softdog_preticktock);

	return 0;
}