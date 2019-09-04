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
typedef  int /*<<< orphan*/  u32 ;
struct fimc_dev {scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIMC_REG_CIREAL_ISIZE_AUTOLOAD_EN ; 
 scalar_t__ FIMC_REG_ORGISIZE ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void fimc_hw_en_autoload(struct fimc_dev *dev, int enable)
{
	u32 cfg = readl(dev->regs + FIMC_REG_ORGISIZE);
	if (enable)
		cfg |= FIMC_REG_CIREAL_ISIZE_AUTOLOAD_EN;
	else
		cfg &= ~FIMC_REG_CIREAL_ISIZE_AUTOLOAD_EN;
	writel(cfg, dev->regs + FIMC_REG_ORGISIZE);
}