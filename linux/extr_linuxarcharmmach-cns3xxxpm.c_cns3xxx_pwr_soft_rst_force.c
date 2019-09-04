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
typedef  unsigned int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  PM_SOFT_RST_REG ; 
 unsigned int PM_SOFT_RST_REG_MASK ; 
 unsigned int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cns3xxx_pwr_soft_rst_force(unsigned int block)
{
	u32 reg = __raw_readl(PM_SOFT_RST_REG);

	/*
	 * bit 0, 28, 29 => program low to reset,
	 * the other else program low and then high
	 */
	if (block & 0x30000001) {
		reg &= ~(block & PM_SOFT_RST_REG_MASK);
	} else {
		reg &= ~(block & PM_SOFT_RST_REG_MASK);
		__raw_writel(reg, PM_SOFT_RST_REG);
		reg |= (block & PM_SOFT_RST_REG_MASK);
	}

	__raw_writel(reg, PM_SOFT_RST_REG);
}