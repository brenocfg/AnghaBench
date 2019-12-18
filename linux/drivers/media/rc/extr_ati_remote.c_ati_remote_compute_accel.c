#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ati_remote {unsigned long acc_jiffies; scalar_t__ old_jiffies; } ;
struct TYPE_3__ {int msecs; int value; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* accel ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 scalar_t__ time_after (unsigned long,scalar_t__) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int ati_remote_compute_accel(struct ati_remote *ati_remote)
{
	unsigned long now = jiffies, reset_time;
	int i;

	reset_time = msecs_to_jiffies(250);

	if (time_after(now, ati_remote->old_jiffies + reset_time)) {
		ati_remote->acc_jiffies = now;
		return 1;
	}
	for (i = 0; i < ARRAY_SIZE(accel) - 1; i++) {
		unsigned long timeout = msecs_to_jiffies(accel[i].msecs);

		if (time_before(now, ati_remote->acc_jiffies + timeout))
			return accel[i].value;
	}
	return accel[i].value;
}