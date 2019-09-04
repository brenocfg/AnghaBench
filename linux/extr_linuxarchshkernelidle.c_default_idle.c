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
 int /*<<< orphan*/  clear_bl_bit () ; 
 int /*<<< orphan*/  cpu_sleep () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  set_bl_bit () ; 

void default_idle(void)
{
	set_bl_bit();
	local_irq_enable();
	/* Isn't this racy ? */
	cpu_sleep();
	clear_bl_bit();
}