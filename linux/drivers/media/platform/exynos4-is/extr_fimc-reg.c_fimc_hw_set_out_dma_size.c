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
struct fimc_frame {int f_height; int f_width; } ;
struct fimc_dev {scalar_t__ regs; } ;
struct fimc_ctx {struct fimc_frame d_frame; struct fimc_dev* fimc_dev; } ;

/* Variables and functions */
 scalar_t__ FIMC_REG_CIGCTRL ; 
 int FIMC_REG_CIGCTRL_CSC_ITU601_709 ; 
 scalar_t__ FIMC_REG_ORGOSIZE ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void fimc_hw_set_out_dma_size(struct fimc_ctx *ctx)
{
	struct fimc_dev *dev = ctx->fimc_dev;
	struct fimc_frame *frame = &ctx->d_frame;
	u32 cfg;

	cfg = (frame->f_height << 16) | frame->f_width;
	writel(cfg, dev->regs + FIMC_REG_ORGOSIZE);

	/* Select color space conversion equation (HD/SD size).*/
	cfg = readl(dev->regs + FIMC_REG_CIGCTRL);
	if (frame->f_width >= 1280) /* HD */
		cfg |= FIMC_REG_CIGCTRL_CSC_ITU601_709;
	else	/* SD */
		cfg &= ~FIMC_REG_CIGCTRL_CSC_ITU601_709;
	writel(cfg, dev->regs + FIMC_REG_CIGCTRL);

}