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
struct mmc_davinci_host {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ DAVINCI_MMCCTL ; 
 int MMCCTL_CMDRST ; 
 int MMCCTL_DATRST ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static inline void mmc_davinci_reset_ctrl(struct mmc_davinci_host *host,
								int val)
{
	u32 temp;

	temp = readl(host->base + DAVINCI_MMCCTL);
	if (val)	/* reset */
		temp |= MMCCTL_CMDRST | MMCCTL_DATRST;
	else		/* enable */
		temp &= ~(MMCCTL_CMDRST | MMCCTL_DATRST);

	writel(temp, host->base + DAVINCI_MMCCTL);
	udelay(10);
}