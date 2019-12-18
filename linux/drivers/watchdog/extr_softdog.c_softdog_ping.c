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
struct watchdog_device {scalar_t__ pretimeout; scalar_t__ timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SOFT_WATCHDOG_PRETIMEOUT ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_set (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  softdog_preticktock ; 
 int /*<<< orphan*/  softdog_ticktock ; 

__attribute__((used)) static int softdog_ping(struct watchdog_device *w)
{
	if (!hrtimer_active(&softdog_ticktock))
		__module_get(THIS_MODULE);
	hrtimer_start(&softdog_ticktock, ktime_set(w->timeout, 0),
		      HRTIMER_MODE_REL);

	if (IS_ENABLED(CONFIG_SOFT_WATCHDOG_PRETIMEOUT)) {
		if (w->pretimeout)
			hrtimer_start(&softdog_preticktock,
				      ktime_set(w->timeout - w->pretimeout, 0),
				      HRTIMER_MODE_REL);
		else
			hrtimer_cancel(&softdog_preticktock);
	}

	return 0;
}