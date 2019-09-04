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
 scalar_t__ cmm_alloc_pages (scalar_t__) ; 
 int /*<<< orphan*/  cmm_dbg (char*,...) ; 
 int /*<<< orphan*/  cmm_free_pages (scalar_t__) ; 
 int /*<<< orphan*/  cmm_get_mpp () ; 
 int delay ; 
 int hotplug_delay ; 
 int /*<<< orphan*/  hotplug_mutex ; 
 scalar_t__ hotplug_occurred ; 
 scalar_t__ kthread_should_stop () ; 
 scalar_t__ loaned_pages ; 
 scalar_t__ loaned_pages_target ; 
 unsigned long msleep_interruptible (int) ; 
 scalar_t__ mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cmm_thread(void *dummy)
{
	unsigned long timeleft;

	while (1) {
		timeleft = msleep_interruptible(delay * 1000);

		if (kthread_should_stop() || timeleft)
			break;

		if (mutex_trylock(&hotplug_mutex)) {
			if (hotplug_occurred) {
				hotplug_occurred = 0;
				mutex_unlock(&hotplug_mutex);
				cmm_dbg("Hotplug operation has occurred, "
						"loaning activity suspended "
						"for %d seconds.\n",
						hotplug_delay);
				timeleft = msleep_interruptible(hotplug_delay *
						1000);
				if (kthread_should_stop() || timeleft)
					break;
				continue;
			}
			mutex_unlock(&hotplug_mutex);
		} else {
			cmm_dbg("Hotplug operation in progress, activity "
					"suspended\n");
			continue;
		}

		cmm_get_mpp();

		if (loaned_pages_target > loaned_pages) {
			if (cmm_alloc_pages(loaned_pages_target - loaned_pages))
				loaned_pages_target = loaned_pages;
		} else if (loaned_pages_target < loaned_pages)
			cmm_free_pages(loaned_pages - loaned_pages_target);
	}
	return 0;
}