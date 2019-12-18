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
struct fimc_dma_offset {int y_v; int y_h; int cb_v; int cb_h; int cr_v; int cr_h; } ;
struct fimc_frame {struct fimc_fmt* fmt; struct fimc_dma_offset dma_offset; } ;
struct fimc_fmt {int colplanes; scalar_t__ color; } ;
struct fimc_dev {scalar_t__ regs; } ;
struct fimc_ctx {int out_order_1p; int out_order_2p; struct fimc_frame d_frame; struct fimc_dev* fimc_dev; } ;

/* Variables and functions */
 scalar_t__ FIMC_FMT_RGB444 ; 
 scalar_t__ FIMC_FMT_RGB555 ; 
 scalar_t__ FIMC_FMT_RGB565 ; 
 scalar_t__ FIMC_REG_CIOCBOFF ; 
 scalar_t__ FIMC_REG_CIOCROFF ; 
 scalar_t__ FIMC_REG_CIOCTRL ; 
 int FIMC_REG_CIOCTRL_ARGB1555 ; 
 int FIMC_REG_CIOCTRL_ARGB4444 ; 
 int FIMC_REG_CIOCTRL_ORDER2P_MASK ; 
 int FIMC_REG_CIOCTRL_ORDER422_MASK ; 
 int FIMC_REG_CIOCTRL_RGB16FMT_MASK ; 
 int FIMC_REG_CIOCTRL_RGB565 ; 
 int FIMC_REG_CIOCTRL_YCBCR_2PLANE ; 
 int FIMC_REG_CIOCTRL_YCBCR_3PLANE ; 
 int FIMC_REG_CIOCTRL_YCBCR_PLANE_MASK ; 
 scalar_t__ FIMC_REG_CIOYOFF ; 
 int /*<<< orphan*/  fimc_hw_set_out_dma_size (struct fimc_ctx*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void fimc_hw_set_out_dma(struct fimc_ctx *ctx)
{
	struct fimc_dev *dev = ctx->fimc_dev;
	struct fimc_frame *frame = &ctx->d_frame;
	struct fimc_dma_offset *offset = &frame->dma_offset;
	struct fimc_fmt *fmt = frame->fmt;
	u32 cfg;

	/* Set the input dma offsets. */
	cfg = (offset->y_v << 16) | offset->y_h;
	writel(cfg, dev->regs + FIMC_REG_CIOYOFF);

	cfg = (offset->cb_v << 16) | offset->cb_h;
	writel(cfg, dev->regs + FIMC_REG_CIOCBOFF);

	cfg = (offset->cr_v << 16) | offset->cr_h;
	writel(cfg, dev->regs + FIMC_REG_CIOCROFF);

	fimc_hw_set_out_dma_size(ctx);

	/* Configure chroma components order. */
	cfg = readl(dev->regs + FIMC_REG_CIOCTRL);

	cfg &= ~(FIMC_REG_CIOCTRL_ORDER2P_MASK |
		 FIMC_REG_CIOCTRL_ORDER422_MASK |
		 FIMC_REG_CIOCTRL_YCBCR_PLANE_MASK |
		 FIMC_REG_CIOCTRL_RGB16FMT_MASK);

	if (fmt->colplanes == 1)
		cfg |= ctx->out_order_1p;
	else if (fmt->colplanes == 2)
		cfg |= ctx->out_order_2p | FIMC_REG_CIOCTRL_YCBCR_2PLANE;
	else if (fmt->colplanes == 3)
		cfg |= FIMC_REG_CIOCTRL_YCBCR_3PLANE;

	if (fmt->color == FIMC_FMT_RGB565)
		cfg |= FIMC_REG_CIOCTRL_RGB565;
	else if (fmt->color == FIMC_FMT_RGB555)
		cfg |= FIMC_REG_CIOCTRL_ARGB1555;
	else if (fmt->color == FIMC_FMT_RGB444)
		cfg |= FIMC_REG_CIOCTRL_ARGB4444;

	writel(cfg, dev->regs + FIMC_REG_CIOCTRL);
}