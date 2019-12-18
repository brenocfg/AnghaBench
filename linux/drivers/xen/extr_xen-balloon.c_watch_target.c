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
struct xenbus_watch {int dummy; } ;
struct TYPE_2__ {unsigned long long target_pages; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  XBT_NIL ; 
 int /*<<< orphan*/  balloon_set_new_target (unsigned long long) ; 
 TYPE_1__ balloon_stats ; 
 scalar_t__ max_mem_size ; 
 scalar_t__ xen_initial_domain () ; 
 scalar_t__ xen_pv_domain () ; 
 scalar_t__ xen_saved_max_mem_size ; 
 int xenbus_scanf (int /*<<< orphan*/ ,char*,char*,char*,unsigned long long*) ; 

__attribute__((used)) static void watch_target(struct xenbus_watch *watch,
			 const char *path, const char *token)
{
	unsigned long long new_target, static_max;
	int err;
	static bool watch_fired;
	static long target_diff;

#ifdef CONFIG_MEMORY_HOTPLUG
	/* The balloon driver will take care of adding memory now. */
	if (xen_saved_max_mem_size)
		max_mem_size = xen_saved_max_mem_size;
#endif

	err = xenbus_scanf(XBT_NIL, "memory", "target", "%llu", &new_target);
	if (err != 1) {
		/* This is ok (for domain0 at least) - so just return */
		return;
	}

	/* The given memory/target value is in KiB, so it needs converting to
	 * pages. PAGE_SHIFT converts bytes to pages, hence PAGE_SHIFT - 10.
	 */
	new_target >>= PAGE_SHIFT - 10;

	if (!watch_fired) {
		watch_fired = true;

		if ((xenbus_scanf(XBT_NIL, "memory", "static-max",
				  "%llu", &static_max) == 1) ||
		    (xenbus_scanf(XBT_NIL, "memory", "memory_static_max",
				  "%llu", &static_max) == 1))
			static_max >>= PAGE_SHIFT - 10;
		else
			static_max = new_target;

		target_diff = (xen_pv_domain() || xen_initial_domain()) ? 0
				: static_max - balloon_stats.target_pages;
	}

	balloon_set_new_target(new_target - target_diff);
}