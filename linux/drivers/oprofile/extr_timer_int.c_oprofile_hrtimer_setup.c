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
 int /*<<< orphan*/  CPUHP_AP_ONLINE_DYN ; 
 int cpuhp_setup_state_nocalls (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hp_online ; 
 int /*<<< orphan*/  oprofile_timer_online ; 
 int /*<<< orphan*/  oprofile_timer_prep_down ; 

__attribute__((used)) static int oprofile_hrtimer_setup(void)
{
	int ret;

	ret = cpuhp_setup_state_nocalls(CPUHP_AP_ONLINE_DYN,
					"oprofile/timer:online",
					oprofile_timer_online,
					oprofile_timer_prep_down);
	if (ret < 0)
		return ret;
	hp_online = ret;
	return 0;
}