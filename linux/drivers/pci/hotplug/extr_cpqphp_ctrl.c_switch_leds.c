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
typedef  int u32 ;
struct controller {scalar_t__ hpc_reg; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ LED_CONTROL ; 
 int /*<<< orphan*/  long_delay (int) ; 
 int /*<<< orphan*/  set_SOGO (struct controller*) ; 
 int /*<<< orphan*/  wait_for_ctrl_irq (struct controller*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void switch_leds(struct controller *ctrl, const int num_of_slots,
			u32 *work_LED, const int direction)
{
	int loop;

	for (loop = 0; loop < num_of_slots; loop++) {
		if (direction)
			*work_LED = *work_LED >> 1;
		else
			*work_LED = *work_LED << 1;
		writel(*work_LED, ctrl->hpc_reg + LED_CONTROL);

		set_SOGO(ctrl);

		/* Wait for SOGO interrupt */
		wait_for_ctrl_irq(ctrl);

		/* Get ready for next iteration */
		long_delay((2*HZ)/10);
	}
}