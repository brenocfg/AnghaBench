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

/* Variables and functions */
 int EIO ; 
 int ETIME ; 
 int /*<<< orphan*/  LPC_NSEC_PERWAIT ; 
 int LPC_REG_OP_STATUS ; 
 int LPC_REG_OP_STATUS_FINISHED ; 
 int LPC_REG_OP_STATUS_IDLE ; 
 int /*<<< orphan*/  ndelay (int /*<<< orphan*/ ) ; 
 int readl (unsigned char*) ; 

__attribute__((used)) static int wait_lpc_idle(unsigned char *mbase, unsigned int waitcnt)
{
	u32 status;

	do {
		status = readl(mbase + LPC_REG_OP_STATUS);
		if (status & LPC_REG_OP_STATUS_IDLE)
			return (status & LPC_REG_OP_STATUS_FINISHED) ? 0 : -EIO;
		ndelay(LPC_NSEC_PERWAIT);
	} while (--waitcnt);

	return -ETIME;
}