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
struct stfsm {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  STFSM_MAX_WAIT_SEQ_MS ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ stfsm_is_idle (struct stfsm*) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 

__attribute__((used)) static void stfsm_wait_seq(struct stfsm *fsm)
{
	unsigned long deadline;
	int timeout = 0;

	deadline = jiffies + msecs_to_jiffies(STFSM_MAX_WAIT_SEQ_MS);

	while (!timeout) {
		if (time_after_eq(jiffies, deadline))
			timeout = 1;

		if (stfsm_is_idle(fsm))
			return;

		cond_resched();
	}

	dev_err(fsm->dev, "timeout on sequence completion\n");
}