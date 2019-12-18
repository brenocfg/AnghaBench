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
struct fimc_lite {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ FLITE_REG_CIGCTRL ; 
 int FLITE_REG_CIGCTRL_SWRST ; 
 int FLITE_REG_CIGCTRL_SWRST_RDY ; 
 int FLITE_REG_CIGCTRL_SWRST_REQ ; 
 int /*<<< orphan*/  FLITE_RESET_TIMEOUT ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 scalar_t__ time_is_after_jiffies (unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void flite_hw_reset(struct fimc_lite *dev)
{
	unsigned long end = jiffies + msecs_to_jiffies(FLITE_RESET_TIMEOUT);
	u32 cfg;

	cfg = readl(dev->regs + FLITE_REG_CIGCTRL);
	cfg |= FLITE_REG_CIGCTRL_SWRST_REQ;
	writel(cfg, dev->regs + FLITE_REG_CIGCTRL);

	while (time_is_after_jiffies(end)) {
		cfg = readl(dev->regs + FLITE_REG_CIGCTRL);
		if (cfg & FLITE_REG_CIGCTRL_SWRST_RDY)
			break;
		usleep_range(1000, 5000);
	}

	cfg |= FLITE_REG_CIGCTRL_SWRST;
	writel(cfg, dev->regs + FLITE_REG_CIGCTRL);
}