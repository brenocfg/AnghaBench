#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct gsc_frame {TYPE_3__* fmt; } ;
struct gsc_dev {scalar_t__ regs; } ;
struct TYPE_5__ {TYPE_1__* global_alpha; } ;
struct gsc_ctx {TYPE_2__ gsc_ctrls; struct gsc_frame d_frame; struct gsc_dev* gsc_dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  color; } ;
struct TYPE_4__ {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 scalar_t__ GSC_OUT_CON ; 
 int /*<<< orphan*/  GSC_OUT_GLOBAL_ALPHA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GSC_OUT_GLOBAL_ALPHA_MASK ; 
 int /*<<< orphan*/  is_rgb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void gsc_hw_set_global_alpha(struct gsc_ctx *ctx)
{
	struct gsc_dev *dev = ctx->gsc_dev;
	struct gsc_frame *frame = &ctx->d_frame;
	u32 cfg;

	if (!is_rgb(frame->fmt->color)) {
		pr_debug("Not a RGB format");
		return;
	}

	cfg = readl(dev->regs + GSC_OUT_CON);
	cfg &= ~GSC_OUT_GLOBAL_ALPHA_MASK;

	cfg |= GSC_OUT_GLOBAL_ALPHA(ctx->gsc_ctrls.global_alpha->val);
	writel(cfg, dev->regs + GSC_OUT_CON);
}