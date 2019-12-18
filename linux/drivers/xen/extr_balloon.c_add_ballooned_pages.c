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
typedef  enum bp_state { ____Placeholder_bp_state } bp_state ;

/* Variables and functions */
 int BP_DONE ; 
 int BP_ECANCELED ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_USER ; 
 int /*<<< orphan*/  balloon_mutex ; 
 int /*<<< orphan*/  balloon_wq ; 
 int /*<<< orphan*/  ballooned_pages ; 
 int decrease_reservation (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int reserve_additional_memory () ; 
 int si_mem_available () ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 scalar_t__ xen_hotplug_unpopulated ; 

__attribute__((used)) static int add_ballooned_pages(int nr_pages)
{
	enum bp_state st;

	if (xen_hotplug_unpopulated) {
		st = reserve_additional_memory();
		if (st != BP_ECANCELED) {
			mutex_unlock(&balloon_mutex);
			wait_event(balloon_wq,
				   !list_empty(&ballooned_pages));
			mutex_lock(&balloon_mutex);
			return 0;
		}
	}

	if (si_mem_available() < nr_pages)
		return -ENOMEM;

	st = decrease_reservation(nr_pages, GFP_USER);
	if (st != BP_DONE)
		return -ENOMEM;

	return 0;
}