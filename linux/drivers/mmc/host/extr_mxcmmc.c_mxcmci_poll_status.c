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
struct mxcmci_host {int /*<<< orphan*/  clock; } ;

/* Variables and functions */
 unsigned long HZ ; 
 int /*<<< orphan*/  MMC_REG_STATUS ; 
 int STATUS_ERR_MASK ; 
 int STATUS_TIME_OUT_READ ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned long jiffies ; 
 int mxcmci_readl (struct mxcmci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxcmci_set_clk_rate (struct mxcmci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxcmci_softreset (struct mxcmci_host*) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int mxcmci_poll_status(struct mxcmci_host *host, u32 mask)
{
	u32 stat;
	unsigned long timeout = jiffies + HZ;

	do {
		stat = mxcmci_readl(host, MMC_REG_STATUS);
		if (stat & STATUS_ERR_MASK)
			return stat;
		if (time_after(jiffies, timeout)) {
			mxcmci_softreset(host);
			mxcmci_set_clk_rate(host, host->clock);
			return STATUS_TIME_OUT_READ;
		}
		if (stat & mask)
			return 0;
		cpu_relax();
	} while (1);
}