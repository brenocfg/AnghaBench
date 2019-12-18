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
struct fimc_frame {int alpha; TYPE_1__* fmt; } ;
struct fimc_dev {scalar_t__ regs; } ;
struct fimc_ctx {struct fimc_frame d_frame; struct fimc_dev* fimc_dev; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 scalar_t__ FIMC_REG_CIOCTRL ; 
 int FIMC_REG_CIOCTRL_ALPHA_OUT_MASK ; 
 int FMT_HAS_ALPHA ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void fimc_hw_set_rgb_alpha(struct fimc_ctx *ctx)
{
	struct fimc_dev *dev = ctx->fimc_dev;
	struct fimc_frame *frame = &ctx->d_frame;
	u32 cfg;

	if (!(frame->fmt->flags & FMT_HAS_ALPHA))
		return;

	cfg = readl(dev->regs + FIMC_REG_CIOCTRL);
	cfg &= ~FIMC_REG_CIOCTRL_ALPHA_OUT_MASK;
	cfg |= (frame->alpha << 4);
	writel(cfg, dev->regs + FIMC_REG_CIOCTRL);
}