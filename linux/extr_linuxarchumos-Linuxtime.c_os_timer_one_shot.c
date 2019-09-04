#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_4__ {unsigned long long tv_sec; unsigned long long tv_nsec; } ;
struct itimerspec {TYPE_1__ it_interval; TYPE_2__ it_value; } ;

/* Variables and functions */
 unsigned long long UM_NSEC_PER_SEC ; 
 int /*<<< orphan*/  event_high_res_timer ; 
 int /*<<< orphan*/  timer_settime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct itimerspec*,int /*<<< orphan*/ *) ; 

int os_timer_one_shot(int ticks)
{
	struct itimerspec its;
	unsigned long long nsec;
	unsigned long sec;

    nsec = (ticks + 1);
    sec = nsec / UM_NSEC_PER_SEC;
	nsec = nsec % UM_NSEC_PER_SEC;

	its.it_value.tv_sec = nsec / UM_NSEC_PER_SEC;
	its.it_value.tv_nsec = nsec;

	its.it_interval.tv_sec = 0;
	its.it_interval.tv_nsec = 0; // we cheat here

	timer_settime(event_high_res_timer, 0, &its, NULL);
	return 0;
}