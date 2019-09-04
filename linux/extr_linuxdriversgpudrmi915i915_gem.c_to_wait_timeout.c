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
typedef  scalar_t__ s64 ;

/* Variables and functions */
 unsigned long MAX_SCHEDULE_TIMEOUT ; 
 unsigned long nsecs_to_jiffies_timeout (scalar_t__) ; 

__attribute__((used)) static unsigned long to_wait_timeout(s64 timeout_ns)
{
	if (timeout_ns < 0)
		return MAX_SCHEDULE_TIMEOUT;

	if (timeout_ns == 0)
		return 0;

	return nsecs_to_jiffies_timeout(timeout_ns);
}