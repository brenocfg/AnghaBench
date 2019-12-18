#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct fimc_dev {TYPE_1__* drv_data; scalar_t__ regs; } ;
struct TYPE_2__ {int out_buf_count; } ;

/* Variables and functions */
 scalar_t__ FIMC_REG_CIGCTRL ; 
 int FIMC_REG_CIGCTRL_IRQ_LEVEL ; 
 int FIMC_REG_CIGCTRL_SWRST ; 
 scalar_t__ FIMC_REG_CISRCFMT ; 
 int FIMC_REG_CISRCFMT_ITU601_8BIT ; 
 int /*<<< orphan*/  fimc_hw_set_dma_seq (struct fimc_dev*,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void fimc_hw_reset(struct fimc_dev *dev)
{
	u32 cfg;

	cfg = readl(dev->regs + FIMC_REG_CISRCFMT);
	cfg |= FIMC_REG_CISRCFMT_ITU601_8BIT;
	writel(cfg, dev->regs + FIMC_REG_CISRCFMT);

	/* Software reset. */
	cfg = readl(dev->regs + FIMC_REG_CIGCTRL);
	cfg |= (FIMC_REG_CIGCTRL_SWRST | FIMC_REG_CIGCTRL_IRQ_LEVEL);
	writel(cfg, dev->regs + FIMC_REG_CIGCTRL);
	udelay(10);

	cfg = readl(dev->regs + FIMC_REG_CIGCTRL);
	cfg &= ~FIMC_REG_CIGCTRL_SWRST;
	writel(cfg, dev->regs + FIMC_REG_CIGCTRL);

	if (dev->drv_data->out_buf_count > 4)
		fimc_hw_set_dma_seq(dev, 0xF);
}