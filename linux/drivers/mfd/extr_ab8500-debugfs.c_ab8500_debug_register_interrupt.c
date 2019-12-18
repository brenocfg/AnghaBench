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
 int num_interrupt_lines ; 
 int /*<<< orphan*/ * num_interrupts ; 

void ab8500_debug_register_interrupt(int line)
{
	if (line < num_interrupt_lines)
		num_interrupts[line]++;
}