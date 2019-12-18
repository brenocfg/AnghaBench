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
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  current ; 
 long msecs_to_jiffies (unsigned int) ; 
 long schedule_timeout (long) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int signal_pending (int /*<<< orphan*/ ) ; 

int cx18_msleep_timeout(unsigned int msecs, int intr)
{
	long int timeout = msecs_to_jiffies(msecs);
	int sig;

	do {
		set_current_state(intr ? TASK_INTERRUPTIBLE : TASK_UNINTERRUPTIBLE);
		timeout = schedule_timeout(timeout);
		sig = intr ? signal_pending(current) : 0;
	} while (!sig && timeout);
	return sig;
}