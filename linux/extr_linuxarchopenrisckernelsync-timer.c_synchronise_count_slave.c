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
 int /*<<< orphan*/  COUNTON ; 
 int NR_LOOPS ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  count_count_start ; 
 int /*<<< orphan*/  count_count_stop ; 
 int /*<<< orphan*/  initcount ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  openrisc_timer_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openrisc_timer_set_next (int /*<<< orphan*/ ) ; 

void synchronise_count_slave(int cpu)
{
	int i;

	/*
	 * Not every cpu is online at the time this gets called,
	 * so we first wait for the master to say everyone is ready
	 */

	for (i = 0; i < NR_LOOPS; i++) {
		atomic_inc(&count_count_start);
		while (atomic_read(&count_count_start) != 2)
			mb();

		/*
		 * Everyone initialises count in the last loop:
		 */
		if (i == NR_LOOPS-1)
			openrisc_timer_set(initcount);

		atomic_inc(&count_count_stop);
		while (atomic_read(&count_count_stop) != 2)
			mb();
	}
	/* Arrange for an interrupt in a short while */
	openrisc_timer_set_next(COUNTON);
}