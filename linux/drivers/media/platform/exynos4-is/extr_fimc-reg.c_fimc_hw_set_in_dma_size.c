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
struct fimc_frame {int f_height; int f_width; int height; int width; } ;
struct fimc_dev {scalar_t__ regs; } ;
struct fimc_ctx {scalar_t__ out_path; struct fimc_frame s_frame; struct fimc_dev* fimc_dev; } ;

/* Variables and functions */
 scalar_t__ FIMC_IO_LCDFIFO ; 
 scalar_t__ FIMC_REG_CIREAL_ISIZE ; 
 int FIMC_REG_CIREAL_ISIZE_AUTOLOAD_EN ; 
 scalar_t__ FIMC_REG_ORGISIZE ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void fimc_hw_set_in_dma_size(struct fimc_ctx *ctx)
{
	struct fimc_dev *dev = ctx->fimc_dev;
	struct fimc_frame *frame = &ctx->s_frame;
	u32 cfg_o = 0;
	u32 cfg_r = 0;

	if (FIMC_IO_LCDFIFO == ctx->out_path)
		cfg_r |= FIMC_REG_CIREAL_ISIZE_AUTOLOAD_EN;

	cfg_o |= (frame->f_height << 16) | frame->f_width;
	cfg_r |= (frame->height << 16) | frame->width;

	writel(cfg_o, dev->regs + FIMC_REG_ORGISIZE);
	writel(cfg_r, dev->regs + FIMC_REG_CIREAL_ISIZE);
}