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
typedef  int /*<<< orphan*/  u32 ;
struct gsc_frame {scalar_t__ colorspace; TYPE_1__* fmt; } ;
struct gsc_dev {scalar_t__ regs; } ;
struct gsc_ctx {struct gsc_frame s_frame; struct gsc_dev* gsc_dev; } ;
struct TYPE_2__ {scalar_t__ pixelformat; } ;

/* Variables and functions */
 scalar_t__ GSC_IN_CON ; 
 int /*<<< orphan*/  GSC_IN_RGB565 ; 
 int /*<<< orphan*/  GSC_IN_RGB_HD_WIDE ; 
 int /*<<< orphan*/  GSC_IN_RGB_SD_WIDE ; 
 int /*<<< orphan*/  GSC_IN_XRGB8888 ; 
 scalar_t__ V4L2_COLORSPACE_REC709 ; 
 scalar_t__ V4L2_PIX_FMT_RGB32 ; 
 scalar_t__ V4L2_PIX_FMT_RGB565X ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void gsc_hw_set_in_image_rgb(struct gsc_ctx *ctx)
{
	struct gsc_dev *dev = ctx->gsc_dev;
	struct gsc_frame *frame = &ctx->s_frame;
	u32 cfg;

	cfg = readl(dev->regs + GSC_IN_CON);
	if (frame->colorspace == V4L2_COLORSPACE_REC709)
		cfg |= GSC_IN_RGB_HD_WIDE;
	else
		cfg |= GSC_IN_RGB_SD_WIDE;

	if (frame->fmt->pixelformat == V4L2_PIX_FMT_RGB565X)
		cfg |= GSC_IN_RGB565;
	else if (frame->fmt->pixelformat == V4L2_PIX_FMT_RGB32)
		cfg |= GSC_IN_XRGB8888;

	writel(cfg, dev->regs + GSC_IN_CON);
}