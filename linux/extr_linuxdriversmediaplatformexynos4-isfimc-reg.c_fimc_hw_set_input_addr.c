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
struct fimc_addr {int /*<<< orphan*/  cr; int /*<<< orphan*/  cb; int /*<<< orphan*/  y; } ;

/* Variables and functions */
 scalar_t__ FIMC_REG_CIICBSA (int /*<<< orphan*/ ) ; 
 scalar_t__ FIMC_REG_CIICRSA (int /*<<< orphan*/ ) ; 
 scalar_t__ FIMC_REG_CIIYSA (int /*<<< orphan*/ ) ; 
 scalar_t__ FIMC_REG_CIREAL_ISIZE ; 
 int /*<<< orphan*/  FIMC_REG_CIREAL_ISIZE_ADDR_CH_DIS ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void fimc_hw_set_input_addr(struct fimc_dev *dev, struct fimc_addr *paddr)
{
	u32 cfg = readl(dev->regs + FIMC_REG_CIREAL_ISIZE);
	cfg |= FIMC_REG_CIREAL_ISIZE_ADDR_CH_DIS;
	writel(cfg, dev->regs + FIMC_REG_CIREAL_ISIZE);

	writel(paddr->y, dev->regs + FIMC_REG_CIIYSA(0));
	writel(paddr->cb, dev->regs + FIMC_REG_CIICBSA(0));
	writel(paddr->cr, dev->regs + FIMC_REG_CIICRSA(0));

	cfg &= ~FIMC_REG_CIREAL_ISIZE_ADDR_CH_DIS;
	writel(cfg, dev->regs + FIMC_REG_CIREAL_ISIZE);
}