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
struct gendisk {int events; int async_events; struct disk_events* ev; } ;
struct disk_events {long poll_msecs; } ;

/* Variables and functions */
 long disk_events_dfl_poll_msecs ; 
 unsigned long msecs_to_jiffies (long) ; 

__attribute__((used)) static unsigned long disk_events_poll_jiffies(struct gendisk *disk)
{
	struct disk_events *ev = disk->ev;
	long intv_msecs = 0;

	/*
	 * If device-specific poll interval is set, always use it.  If
	 * the default is being used, poll iff there are events which
	 * can't be monitored asynchronously.
	 */
	if (ev->poll_msecs >= 0)
		intv_msecs = ev->poll_msecs;
	else if (disk->events & ~disk->async_events)
		intv_msecs = disk_events_dfl_poll_msecs;

	return msecs_to_jiffies(intv_msecs);
}