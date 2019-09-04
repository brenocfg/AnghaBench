#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  last_busy; int /*<<< orphan*/  autosuspend_delay; int /*<<< orphan*/  use_autosuspend; } ;
struct device {TYPE_1__ power; } ;

/* Variables and functions */
 void* READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 unsigned long round_jiffies (unsigned long) ; 

unsigned long pm_runtime_autosuspend_expiration(struct device *dev)
{
	int autosuspend_delay;
	long elapsed;
	unsigned long last_busy;
	unsigned long expires = 0;

	if (!dev->power.use_autosuspend)
		goto out;

	autosuspend_delay = READ_ONCE(dev->power.autosuspend_delay);
	if (autosuspend_delay < 0)
		goto out;

	last_busy = READ_ONCE(dev->power.last_busy);
	elapsed = jiffies - last_busy;
	if (elapsed < 0)
		goto out;	/* jiffies has wrapped around. */

	/*
	 * If the autosuspend_delay is >= 1 second, align the timer by rounding
	 * up to the nearest second.
	 */
	expires = last_busy + msecs_to_jiffies(autosuspend_delay);
	if (autosuspend_delay >= 1000)
		expires = round_jiffies(expires);
	expires += !expires;
	if (elapsed >= expires - last_busy)
		expires = 0;	/* Already expired. */

 out:
	return expires;
}