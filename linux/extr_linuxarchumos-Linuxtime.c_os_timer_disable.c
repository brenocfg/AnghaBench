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
struct TYPE_2__ {int tv_sec; long long tv_nsec; } ;
struct itimerspec {TYPE_1__ it_value; } ;

/* Variables and functions */
 int UM_NSEC_PER_SEC ; 
 int /*<<< orphan*/  event_high_res_timer ; 
 int /*<<< orphan*/  memset (struct itimerspec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  timer_settime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct itimerspec*,struct itimerspec*) ; 

long long os_timer_disable(void)
{
	struct itimerspec its;

	memset(&its, 0, sizeof(struct itimerspec));
	timer_settime(event_high_res_timer, 0, &its, &its);

	return its.it_value.tv_sec * UM_NSEC_PER_SEC + its.it_value.tv_nsec;
}