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
typedef  scalar_t__ u32 ;
struct hfi1_pportdata {int /*<<< orphan*/  dd; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dd_dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  log_state_transition (struct hfi1_pportdata*,scalar_t__) ; 
 unsigned long msecs_to_jiffies (int) ; 
 scalar_t__ read_physical_state (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int wait_physical_linkstate(struct hfi1_pportdata *ppd, u32 state,
				   int msecs)
{
	u32 read_state;
	unsigned long timeout;

	timeout = jiffies + msecs_to_jiffies(msecs);
	while (1) {
		read_state = read_physical_state(ppd->dd);
		if (read_state == state)
			break;
		if (time_after(jiffies, timeout)) {
			dd_dev_err(ppd->dd,
				   "timeout waiting for phy link state 0x%x\n",
				   state);
			return -ETIMEDOUT;
		}
		usleep_range(1950, 2050); /* sleep 2ms-ish */
	}

	log_state_transition(ppd, state);
	return 0;
}