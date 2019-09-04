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
 int /*<<< orphan*/  pr_warning (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static inline void op_x86_warn_in_use(int counter)
{
	/*
	 * The warning indicates an already running counter. If
	 * oprofile doesn't collect data, then try using a different
	 * performance counter on your platform to monitor the desired
	 * event. Delete counter #%d from the desired event by editing
	 * the /usr/share/oprofile/%s/<cpu>/events file. If the event
	 * cannot be monitored by any other counter, contact your
	 * hardware or BIOS vendor.
	 */
	pr_warning("oprofile: counter #%d on cpu #%d may already be used\n",
		   counter, smp_processor_id());
}