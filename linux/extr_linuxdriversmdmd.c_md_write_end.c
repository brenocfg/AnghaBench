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
struct mddev {int safemode; scalar_t__ safemode_delay; int /*<<< orphan*/  safemode_timer; int /*<<< orphan*/  thread; int /*<<< orphan*/  writes_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  percpu_ref_put (int /*<<< orphan*/ *) ; 
 scalar_t__ roundup (int /*<<< orphan*/ ,scalar_t__) ; 

void md_write_end(struct mddev *mddev)
{
	percpu_ref_put(&mddev->writes_pending);

	if (mddev->safemode == 2)
		md_wakeup_thread(mddev->thread);
	else if (mddev->safemode_delay)
		/* The roundup() ensures this only performs locking once
		 * every ->safemode_delay jiffies
		 */
		mod_timer(&mddev->safemode_timer,
			  roundup(jiffies, mddev->safemode_delay) +
			  mddev->safemode_delay);
}