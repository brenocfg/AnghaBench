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
struct mapped_device {int /*<<< orphan*/  event_nr; int /*<<< orphan*/  eventq; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

int dm_wait_event(struct mapped_device *md, int event_nr)
{
	return wait_event_interruptible(md->eventq,
			(event_nr != atomic_read(&md->event_nr)));
}