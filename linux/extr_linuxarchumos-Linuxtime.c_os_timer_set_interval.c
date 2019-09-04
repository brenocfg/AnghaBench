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
typedef  int /*<<< orphan*/  timer_t ;
struct TYPE_4__ {unsigned long long tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_3__ {unsigned long long tv_nsec; scalar_t__ tv_sec; } ;
struct itimerspec {TYPE_2__ it_interval; TYPE_1__ it_value; } ;

/* Variables and functions */
 unsigned long long UM_HZ ; 
 unsigned long long UM_NSEC_PER_SEC ; 
 int errno ; 
 int /*<<< orphan*/  event_high_res_timer ; 
 int timer_settime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct itimerspec*,int /*<<< orphan*/ *) ; 

int os_timer_set_interval(void* timer, void* i)
{
	struct itimerspec its;
	unsigned long long nsec;
	timer_t* t = timer;
	struct itimerspec* its_in = i;

	if(t == NULL) {
		t = &event_high_res_timer;
	}

	nsec = UM_NSEC_PER_SEC / UM_HZ;

	if(its_in != NULL) {
		its.it_value.tv_sec = its_in->it_value.tv_sec;
		its.it_value.tv_nsec = its_in->it_value.tv_nsec;
	} else {
		its.it_value.tv_sec = 0;
		its.it_value.tv_nsec = nsec;
	}

	its.it_interval.tv_sec = 0;
	its.it_interval.tv_nsec = nsec;

	if(timer_settime(*t, 0, &its, NULL) == -1) {
		return -errno;
	}

	return 0;
}