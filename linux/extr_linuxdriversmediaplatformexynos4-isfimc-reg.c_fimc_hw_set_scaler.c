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
typedef  scalar_t__ u32 ;
struct fimc_scaler {scalar_t__ copy_mode; scalar_t__ scaleup_v; scalar_t__ scaleup_h; int /*<<< orphan*/  enabled; } ;
struct fimc_frame {TYPE_1__* fmt; } ;
struct fimc_dev {scalar_t__ regs; } ;
struct fimc_ctx {int flags; scalar_t__ in_path; scalar_t__ out_path; struct fimc_frame d_frame; struct fimc_frame s_frame; struct fimc_scaler scaler; struct fimc_dev* fimc_dev; } ;
struct TYPE_2__ {int color; } ;

/* Variables and functions */
 int FIMC_COLOR_RANGE_NARROW ; 
 scalar_t__ FIMC_FMT_RGB444 ; 
#define  FIMC_FMT_RGB565 130 
#define  FIMC_FMT_RGB666 129 
#define  FIMC_FMT_RGB888 128 
 scalar_t__ FIMC_IO_DMA ; 
 scalar_t__ FIMC_REG_CISCCTRL ; 
 scalar_t__ FIMC_REG_CISCCTRL_CSCR2Y_WIDE ; 
 scalar_t__ FIMC_REG_CISCCTRL_CSCY2R_WIDE ; 
 scalar_t__ FIMC_REG_CISCCTRL_INRGB_FMT_MASK ; 
 scalar_t__ FIMC_REG_CISCCTRL_INRGB_FMT_RGB565 ; 
 scalar_t__ FIMC_REG_CISCCTRL_INRGB_FMT_RGB666 ; 
 scalar_t__ FIMC_REG_CISCCTRL_INRGB_FMT_RGB888 ; 
 scalar_t__ FIMC_REG_CISCCTRL_INTERLACE ; 
 scalar_t__ FIMC_REG_CISCCTRL_ONE2ONE ; 
 scalar_t__ FIMC_REG_CISCCTRL_OUTRGB_FMT_MASK ; 
 scalar_t__ FIMC_REG_CISCCTRL_OUTRGB_FMT_RGB565 ; 
 scalar_t__ FIMC_REG_CISCCTRL_OUTRGB_FMT_RGB666 ; 
 scalar_t__ FIMC_REG_CISCCTRL_OUTRGB_FMT_RGB888 ; 
 scalar_t__ FIMC_REG_CISCCTRL_RGB_EXT ; 
 scalar_t__ FIMC_REG_CISCCTRL_SCALERBYPASS ; 
 scalar_t__ FIMC_REG_CISCCTRL_SCALEUP_H ; 
 scalar_t__ FIMC_REG_CISCCTRL_SCALEUP_V ; 
 int FIMC_SCAN_MODE_INTERLACED ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void fimc_hw_set_scaler(struct fimc_ctx *ctx)
{
	struct fimc_dev *dev = ctx->fimc_dev;
	struct fimc_scaler *sc = &ctx->scaler;
	struct fimc_frame *src_frame = &ctx->s_frame;
	struct fimc_frame *dst_frame = &ctx->d_frame;

	u32 cfg = readl(dev->regs + FIMC_REG_CISCCTRL);

	cfg &= ~(FIMC_REG_CISCCTRL_CSCR2Y_WIDE | FIMC_REG_CISCCTRL_CSCY2R_WIDE |
		 FIMC_REG_CISCCTRL_SCALEUP_H | FIMC_REG_CISCCTRL_SCALEUP_V |
		 FIMC_REG_CISCCTRL_SCALERBYPASS | FIMC_REG_CISCCTRL_ONE2ONE |
		 FIMC_REG_CISCCTRL_INRGB_FMT_MASK | FIMC_REG_CISCCTRL_OUTRGB_FMT_MASK |
		 FIMC_REG_CISCCTRL_INTERLACE | FIMC_REG_CISCCTRL_RGB_EXT);

	if (!(ctx->flags & FIMC_COLOR_RANGE_NARROW))
		cfg |= (FIMC_REG_CISCCTRL_CSCR2Y_WIDE |
			FIMC_REG_CISCCTRL_CSCY2R_WIDE);

	if (!sc->enabled)
		cfg |= FIMC_REG_CISCCTRL_SCALERBYPASS;

	if (sc->scaleup_h)
		cfg |= FIMC_REG_CISCCTRL_SCALEUP_H;

	if (sc->scaleup_v)
		cfg |= FIMC_REG_CISCCTRL_SCALEUP_V;

	if (sc->copy_mode)
		cfg |= FIMC_REG_CISCCTRL_ONE2ONE;

	if (ctx->in_path == FIMC_IO_DMA) {
		switch (src_frame->fmt->color) {
		case FIMC_FMT_RGB565:
			cfg |= FIMC_REG_CISCCTRL_INRGB_FMT_RGB565;
			break;
		case FIMC_FMT_RGB666:
			cfg |= FIMC_REG_CISCCTRL_INRGB_FMT_RGB666;
			break;
		case FIMC_FMT_RGB888:
			cfg |= FIMC_REG_CISCCTRL_INRGB_FMT_RGB888;
			break;
		}
	}

	if (ctx->out_path == FIMC_IO_DMA) {
		u32 color = dst_frame->fmt->color;

		if (color >= FIMC_FMT_RGB444 && color <= FIMC_FMT_RGB565)
			cfg |= FIMC_REG_CISCCTRL_OUTRGB_FMT_RGB565;
		else if (color == FIMC_FMT_RGB666)
			cfg |= FIMC_REG_CISCCTRL_OUTRGB_FMT_RGB666;
		else if (color == FIMC_FMT_RGB888)
			cfg |= FIMC_REG_CISCCTRL_OUTRGB_FMT_RGB888;
	} else {
		cfg |= FIMC_REG_CISCCTRL_OUTRGB_FMT_RGB888;

		if (ctx->flags & FIMC_SCAN_MODE_INTERLACED)
			cfg |= FIMC_REG_CISCCTRL_INTERLACE;
	}

	writel(cfg, dev->regs + FIMC_REG_CISCCTRL);
}