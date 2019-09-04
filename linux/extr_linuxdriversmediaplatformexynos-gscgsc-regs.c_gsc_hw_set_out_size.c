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
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct gsc_frame {TYPE_3__ crop; int /*<<< orphan*/  f_height; int /*<<< orphan*/  f_width; } ;
struct gsc_dev {scalar_t__ regs; } ;
struct TYPE_5__ {TYPE_1__* rotate; } ;
struct gsc_ctx {scalar_t__ out_path; TYPE_2__ gsc_ctrls; struct gsc_frame d_frame; struct gsc_dev* gsc_dev; } ;
struct TYPE_4__ {int val; } ;

/* Variables and functions */
 scalar_t__ GSC_DMA ; 
 int /*<<< orphan*/  GSC_DSTIMG_HEIGHT (int /*<<< orphan*/ ) ; 
 scalar_t__ GSC_DSTIMG_OFFSET ; 
 int /*<<< orphan*/  GSC_DSTIMG_OFFSET_X (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GSC_DSTIMG_OFFSET_Y (int /*<<< orphan*/ ) ; 
 scalar_t__ GSC_DSTIMG_SIZE ; 
 int /*<<< orphan*/  GSC_DSTIMG_WIDTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GSC_SCALED_HEIGHT (int /*<<< orphan*/ ) ; 
 scalar_t__ GSC_SCALED_SIZE ; 
 int /*<<< orphan*/  GSC_SCALED_WIDTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void gsc_hw_set_out_size(struct gsc_ctx *ctx)
{
	struct gsc_dev *dev = ctx->gsc_dev;
	struct gsc_frame *frame = &ctx->d_frame;
	u32 cfg;

	/* Set output original size */
	if (ctx->out_path == GSC_DMA) {
		cfg = GSC_DSTIMG_OFFSET_X(frame->crop.left);
		cfg |= GSC_DSTIMG_OFFSET_Y(frame->crop.top);
		writel(cfg, dev->regs + GSC_DSTIMG_OFFSET);

		cfg = GSC_DSTIMG_WIDTH(frame->f_width);
		cfg |= GSC_DSTIMG_HEIGHT(frame->f_height);
		writel(cfg, dev->regs + GSC_DSTIMG_SIZE);
	}

	/* Set output scaled size */
	if (ctx->gsc_ctrls.rotate->val == 90 ||
	    ctx->gsc_ctrls.rotate->val == 270) {
		cfg = GSC_SCALED_WIDTH(frame->crop.height);
		cfg |= GSC_SCALED_HEIGHT(frame->crop.width);
	} else {
		cfg = GSC_SCALED_WIDTH(frame->crop.width);
		cfg |= GSC_SCALED_HEIGHT(frame->crop.height);
	}
	writel(cfg, dev->regs + GSC_SCALED_SIZE);
}