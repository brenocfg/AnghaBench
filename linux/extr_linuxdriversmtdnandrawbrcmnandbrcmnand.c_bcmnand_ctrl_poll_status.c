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
struct brcmnand_controller {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMNAND_INTFC_STATUS ; 
 int ETIMEDOUT ; 
 unsigned long NAND_POLL_STATUS_TIMEOUT_MS ; 
 int brcmnand_read_reg (struct brcmnand_controller*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,int) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (unsigned long) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int bcmnand_ctrl_poll_status(struct brcmnand_controller *ctrl,
				    u32 mask, u32 expected_val,
				    unsigned long timeout_ms)
{
	unsigned long limit;
	u32 val;

	if (!timeout_ms)
		timeout_ms = NAND_POLL_STATUS_TIMEOUT_MS;

	limit = jiffies + msecs_to_jiffies(timeout_ms);
	do {
		val = brcmnand_read_reg(ctrl, BRCMNAND_INTFC_STATUS);
		if ((val & mask) == expected_val)
			return 0;

		cpu_relax();
	} while (time_after(limit, jiffies));

	dev_warn(ctrl->dev, "timeout on status poll (expected %x got %x)\n",
		 expected_val, val & mask);

	return -ETIMEDOUT;
}