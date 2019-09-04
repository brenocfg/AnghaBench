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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  APPLESMC_CMD_PORT ; 
 int APPLESMC_MAX_WAIT ; 
 int APPLESMC_MIN_WAIT ; 
 int EIO ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int wait_read(void)
{
	u8 status;
	int us;
	for (us = APPLESMC_MIN_WAIT; us < APPLESMC_MAX_WAIT; us <<= 1) {
		udelay(us);
		status = inb(APPLESMC_CMD_PORT);
		/* read: wait for smc to settle */
		if (status & 0x01)
			return 0;
	}

	pr_warn("wait_read() fail: 0x%02x\n", status);
	return -EIO;
}