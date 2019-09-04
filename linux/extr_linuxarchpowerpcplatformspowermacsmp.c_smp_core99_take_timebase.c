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
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  set_tb (int,int) ; 
 int tb_req ; 
 int timebase ; 

__attribute__((used)) static void smp_core99_take_timebase(void)
{
	unsigned long flags;

	local_irq_save(flags);

	tb_req = 1;
	mb();
	while (!timebase)
		barrier();
	mb();
	set_tb(timebase >> 32, timebase & 0xffffffff);
	timebase = 0;
	mb();

	local_irq_restore(flags);
}