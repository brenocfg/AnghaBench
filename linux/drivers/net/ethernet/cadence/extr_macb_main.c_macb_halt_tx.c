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
struct macb {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int MACB_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACB_HALT_TIMEOUT ; 
 int /*<<< orphan*/  NCR ; 
 int /*<<< orphan*/  TGO ; 
 int /*<<< orphan*/  THALT ; 
 int /*<<< orphan*/  TSR ; 
 unsigned long jiffies ; 
 int macb_readl (struct macb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macb_writel (struct macb*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 unsigned long usecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int macb_halt_tx(struct macb *bp)
{
	unsigned long	halt_time, timeout;
	u32		status;

	macb_writel(bp, NCR, macb_readl(bp, NCR) | MACB_BIT(THALT));

	timeout = jiffies + usecs_to_jiffies(MACB_HALT_TIMEOUT);
	do {
		halt_time = jiffies;
		status = macb_readl(bp, TSR);
		if (!(status & MACB_BIT(TGO)))
			return 0;

		udelay(250);
	} while (time_before(halt_time, timeout));

	return -ETIMEDOUT;
}