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
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct gsc_frame {TYPE_1__ crop; int /*<<< orphan*/  f_height; int /*<<< orphan*/  f_width; } ;
struct gsc_dev {scalar_t__ regs; } ;
struct gsc_ctx {struct gsc_frame s_frame; struct gsc_dev* gsc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GSC_CROPPED_HEIGHT (int /*<<< orphan*/ ) ; 
 scalar_t__ GSC_CROPPED_SIZE ; 
 int /*<<< orphan*/  GSC_CROPPED_WIDTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GSC_SRCIMG_HEIGHT (int /*<<< orphan*/ ) ; 
 scalar_t__ GSC_SRCIMG_OFFSET ; 
 int /*<<< orphan*/  GSC_SRCIMG_OFFSET_X (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GSC_SRCIMG_OFFSET_Y (int /*<<< orphan*/ ) ; 
 scalar_t__ GSC_SRCIMG_SIZE ; 
 int /*<<< orphan*/  GSC_SRCIMG_WIDTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void gsc_hw_set_in_size(struct gsc_ctx *ctx)
{
	struct gsc_dev *dev = ctx->gsc_dev;
	struct gsc_frame *frame = &ctx->s_frame;
	u32 cfg;

	/* Set input pixel offset */
	cfg = GSC_SRCIMG_OFFSET_X(frame->crop.left);
	cfg |= GSC_SRCIMG_OFFSET_Y(frame->crop.top);
	writel(cfg, dev->regs + GSC_SRCIMG_OFFSET);

	/* Set input original size */
	cfg = GSC_SRCIMG_WIDTH(frame->f_width);
	cfg |= GSC_SRCIMG_HEIGHT(frame->f_height);
	writel(cfg, dev->regs + GSC_SRCIMG_SIZE);

	/* Set input cropped size */
	cfg = GSC_CROPPED_WIDTH(frame->crop.width);
	cfg |= GSC_CROPPED_HEIGHT(frame->crop.height);
	writel(cfg, dev->regs + GSC_CROPPED_SIZE);
}