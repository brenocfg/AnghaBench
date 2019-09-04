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
typedef  int s64 ;
struct TYPE_2__ {long timeout; } ;

/* Variables and functions */
 long DIV_ROUND_UP (long,int) ; 
 int EINVAL ; 
 int HZ ; 
 long MAX_JIFFY_OFFSET ; 
 int MAX_SEC_IN_JIFFIES ; 
 TYPE_1__* lp_table ; 

__attribute__((used)) static int lp_set_timeout(unsigned int minor, s64 tv_sec, long tv_usec)
{
	long to_jiffies;

	/* Convert to jiffies, place in lp_table */
	if (tv_sec < 0 || tv_usec < 0)
		return -EINVAL;

	/*
	 * we used to not check, so let's not make this fatal,
	 * but deal with user space passing a 32-bit tv_nsec in
	 * a 64-bit field, capping the timeout to 1 second
	 * worth of microseconds, and capping the total at
	 * MAX_JIFFY_OFFSET.
	 */
	if (tv_usec > 999999)
		tv_usec = 999999;

	if (tv_sec >= MAX_SEC_IN_JIFFIES - 1) {
		to_jiffies = MAX_JIFFY_OFFSET;
	} else {
		to_jiffies = DIV_ROUND_UP(tv_usec, 1000000/HZ);
		to_jiffies += tv_sec * (long) HZ;
	}

	if (to_jiffies <= 0) {
		return -EINVAL;
	}
	lp_table[minor].timeout = to_jiffies;
	return 0;
}