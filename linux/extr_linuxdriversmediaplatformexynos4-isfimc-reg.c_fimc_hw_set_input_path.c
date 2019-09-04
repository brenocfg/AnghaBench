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
struct fimc_ctx {scalar_t__ in_path; struct fimc_dev* fimc_dev; } ;

/* Variables and functions */
 scalar_t__ FIMC_IO_DMA ; 
 scalar_t__ FIMC_REG_MSCTRL ; 
 int /*<<< orphan*/  FIMC_REG_MSCTRL_INPUT_EXTCAM ; 
 int /*<<< orphan*/  FIMC_REG_MSCTRL_INPUT_MASK ; 
 int /*<<< orphan*/  FIMC_REG_MSCTRL_INPUT_MEMORY ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void fimc_hw_set_input_path(struct fimc_ctx *ctx)
{
	struct fimc_dev *dev = ctx->fimc_dev;

	u32 cfg = readl(dev->regs + FIMC_REG_MSCTRL);
	cfg &= ~FIMC_REG_MSCTRL_INPUT_MASK;

	if (ctx->in_path == FIMC_IO_DMA)
		cfg |= FIMC_REG_MSCTRL_INPUT_MEMORY;
	else
		cfg |= FIMC_REG_MSCTRL_INPUT_EXTCAM;

	writel(cfg, dev->regs + FIMC_REG_MSCTRL);
}