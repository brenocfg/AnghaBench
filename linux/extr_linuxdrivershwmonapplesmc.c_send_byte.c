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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  APPLESMC_CMD_PORT ; 
 int APPLESMC_MAX_WAIT ; 
 int APPLESMC_MIN_WAIT ; 
 int APPLESMC_RETRY_WAIT ; 
 int EIO ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int send_byte(u8 cmd, u16 port)
{
	u8 status;
	int us;

	outb(cmd, port);
	for (us = APPLESMC_MIN_WAIT; us < APPLESMC_MAX_WAIT; us <<= 1) {
		udelay(us);
		status = inb(APPLESMC_CMD_PORT);
		/* write: wait for smc to settle */
		if (status & 0x02)
			continue;
		/* ready: cmd accepted, return */
		if (status & 0x04)
			return 0;
		/* timeout: give up */
		if (us << 1 == APPLESMC_MAX_WAIT)
			break;
		/* busy: long wait and resend */
		udelay(APPLESMC_RETRY_WAIT);
		outb(cmd, port);
	}

	pr_warn("send_byte(0x%02x, 0x%04x) fail: 0x%02x\n", cmd, port, status);
	return -EIO;
}