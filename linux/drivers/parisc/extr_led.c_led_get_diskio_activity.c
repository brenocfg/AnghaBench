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

/* Variables and functions */
 int LED_DISK_IO ; 
 int NR_VM_EVENT_ITEMS ; 
 size_t PGPGIN ; 
 size_t PGPGOUT ; 
 int /*<<< orphan*/  all_vm_events (unsigned long*) ; 

__attribute__((used)) static __inline__ int led_get_diskio_activity(void)
{	
	static unsigned long last_pgpgin, last_pgpgout;
	unsigned long events[NR_VM_EVENT_ITEMS];
	int changed;

	all_vm_events(events);

	/* Just use a very simple calculation here. Do not care about overflow,
	   since we only want to know if there was activity or not. */
	changed = (events[PGPGIN] != last_pgpgin) ||
		  (events[PGPGOUT] != last_pgpgout);
	last_pgpgin  = events[PGPGIN];
	last_pgpgout = events[PGPGOUT];

	return (changed ? LED_DISK_IO : 0);
}