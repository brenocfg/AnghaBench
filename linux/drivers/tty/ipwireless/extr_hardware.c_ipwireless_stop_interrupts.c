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
struct ipw_hardware {int shutting_down; int /*<<< orphan*/  setup_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_close_hardware (struct ipw_hardware*) ; 

void ipwireless_stop_interrupts(struct ipw_hardware *hw)
{
	if (!hw->shutting_down) {
		/* Tell everyone we are going down. */
		hw->shutting_down = 1;
		del_timer(&hw->setup_timer);

		/* Prevent the hardware from sending any more interrupts */
		do_close_hardware(hw);
	}
}