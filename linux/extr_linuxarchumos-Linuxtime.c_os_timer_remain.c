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
typedef  int /*<<< orphan*/  timer_t ;
struct TYPE_2__ {long tv_nsec; } ;
struct itimerspec {TYPE_1__ it_value; } ;

/* Variables and functions */
 long errno ; 
 int /*<<< orphan*/  event_high_res_timer ; 
 int timer_gettime (int /*<<< orphan*/ *,struct itimerspec*) ; 

long os_timer_remain(void* timer)
{
	struct itimerspec its;
	timer_t* t = timer;

	if(t == NULL) {
		t = &event_high_res_timer;
	}

	if(timer_gettime(t, &its) == -1) {
		return -errno;
	}

	return its.it_value.tv_nsec;
}