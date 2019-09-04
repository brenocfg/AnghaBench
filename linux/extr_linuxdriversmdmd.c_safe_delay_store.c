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
struct mddev {unsigned long safemode_delay; int /*<<< orphan*/  safemode_timer; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 unsigned long HZ ; 
 scalar_t__ jiffies ; 
 scalar_t__ mddev_is_clustered (struct mddev*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 scalar_t__ strict_strtoul_scaled (char const*,unsigned long*,int) ; 

__attribute__((used)) static ssize_t
safe_delay_store(struct mddev *mddev, const char *cbuf, size_t len)
{
	unsigned long msec;

	if (mddev_is_clustered(mddev)) {
		pr_warn("md: Safemode is disabled for clustered mode\n");
		return -EINVAL;
	}

	if (strict_strtoul_scaled(cbuf, &msec, 3) < 0)
		return -EINVAL;
	if (msec == 0)
		mddev->safemode_delay = 0;
	else {
		unsigned long old_delay = mddev->safemode_delay;
		unsigned long new_delay = (msec*HZ)/1000;

		if (new_delay == 0)
			new_delay = 1;
		mddev->safemode_delay = new_delay;
		if (new_delay < old_delay || old_delay == 0)
			mod_timer(&mddev->safemode_timer, jiffies+1);
	}
	return len;
}