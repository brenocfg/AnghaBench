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
struct timer_list {int dummy; } ;
struct garmin_data {scalar_t__ mode; int flags; } ;

/* Variables and functions */
 int FLAGS_QUEUING ; 
 scalar_t__ MODE_NATIVE ; 
 struct garmin_data* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct garmin_data* garmin_data_p ; 
 int /*<<< orphan*/  garmin_flush_queue (struct garmin_data*) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void timeout_handler(struct timer_list *t)
{
	struct garmin_data *garmin_data_p = from_timer(garmin_data_p, t, timer);

	/* send the next queued packet to the tty port */
	if (garmin_data_p->mode == MODE_NATIVE)
		if (garmin_data_p->flags & FLAGS_QUEUING)
			garmin_flush_queue(garmin_data_p);
}