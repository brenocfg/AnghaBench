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
 scalar_t__ chip_to_opa_lstate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dd_dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  read_logical_state (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int wait_logical_linkstate(struct hfi1_pportdata *ppd, u32 state,
				  int msecs)
{
	unsigned long timeout;
	u32 new_state;

	timeout = jiffies + msecs_to_jiffies(msecs);
	while (1) {
		new_state = chip_to_opa_lstate(ppd->dd,
					       read_logical_state(ppd->dd));
		if (new_state == state)
			break;
		if (time_after(jiffies, timeout)) {
			dd_dev_err(ppd->dd,
				   "timeout waiting for link state 0x%x\n",
				   state);
			return -ETIMEDOUT;
		}
		msleep(20);
	}

	return 0;
}