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
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  schedule () ; 

__attribute__((used)) static void
qla83xx_wait_logic(void)
{
	int i;

	/* Yield CPU */
	if (!in_interrupt()) {
		/*
		 * Wait about 200ms before retrying again.
		 * This controls the number of retries for single
		 * lock operation.
		 */
		msleep(100);
		schedule();
	} else {
		for (i = 0; i < 20; i++)
			cpu_relax(); /* This a nop instr on i386 */
	}
}