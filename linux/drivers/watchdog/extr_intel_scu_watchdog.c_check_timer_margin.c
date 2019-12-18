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
 int EINVAL ; 
 int MAX_TIME ; 
 int MIN_TIME_CYCLE ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int) ; 
 int timer_set ; 

__attribute__((used)) static int check_timer_margin(int new_margin)
{
	if ((new_margin < MIN_TIME_CYCLE) ||
	    (new_margin > MAX_TIME - timer_set)) {
		pr_debug("value of new_margin %d is out of the range %d to %d\n",
			 new_margin, MIN_TIME_CYCLE, MAX_TIME - timer_set);
		return -EINVAL;
	}
	return 0;
}