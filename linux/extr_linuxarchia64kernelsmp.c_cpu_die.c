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
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  cpu_halt () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  max_xtp () ; 

void
cpu_die(void)
{
	max_xtp();
	local_irq_disable();
	cpu_halt();
	/* Should never be here */
	BUG();
	for (;;);
}