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
typedef  int /*<<< orphan*/  u32 ;
struct hfi1_devdata {scalar_t__ icode; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ ICODE_FUNCTIONAL_SIMULATOR ; 
 int get_firmware_state (struct hfi1_devdata*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int wait_fm_ready(struct hfi1_devdata *dd, u32 mstimeout)
{
	unsigned long timeout;

	/* in the simulator, the fake 8051 is always ready */
	if (dd->icode == ICODE_FUNCTIONAL_SIMULATOR)
		return 0;

	timeout = msecs_to_jiffies(mstimeout) + jiffies;
	while (1) {
		if (get_firmware_state(dd) == 0xa0)	/* ready */
			return 0;
		if (time_after(jiffies, timeout))	/* timed out */
			return -ETIMEDOUT;
		usleep_range(1950, 2050); /* sleep 2ms-ish */
	}
}