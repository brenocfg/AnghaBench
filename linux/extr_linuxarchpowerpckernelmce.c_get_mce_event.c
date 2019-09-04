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
struct machine_check_event {scalar_t__ in_use; } ;

/* Variables and functions */
 int MAX_MC_EVT ; 
 int /*<<< orphan*/  __this_cpu_dec (int /*<<< orphan*/ ) ; 
 int __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mce_event ; 
 int /*<<< orphan*/  mce_nest_count ; 
 struct machine_check_event* this_cpu_ptr (int /*<<< orphan*/ *) ; 

int get_mce_event(struct machine_check_event *mce, bool release)
{
	int index = __this_cpu_read(mce_nest_count) - 1;
	struct machine_check_event *mc_evt;
	int ret = 0;

	/* Sanity check */
	if (index < 0)
		return ret;

	/* Check if we have MCE info to process. */
	if (index < MAX_MC_EVT) {
		mc_evt = this_cpu_ptr(&mce_event[index]);
		/* Copy the event structure and release the original */
		if (mce)
			*mce = *mc_evt;
		if (release)
			mc_evt->in_use = 0;
		ret = 1;
	}
	/* Decrement the count to free the slot. */
	if (release)
		__this_cpu_dec(mce_nest_count);

	return ret;
}