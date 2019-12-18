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
struct s5p_mfc_regs {int /*<<< orphan*/  e_mslice_size_bits; int /*<<< orphan*/  e_mslice_size_mb; int /*<<< orphan*/  e_mslice_mode; } ;
struct s5p_mfc_dev {struct s5p_mfc_regs* mfc_regs; } ;
struct TYPE_2__ {int mb; int bits; } ;
struct s5p_mfc_ctx {int slice_mode; TYPE_1__ slice_size; struct s5p_mfc_dev* dev; } ;

/* Variables and functions */
 scalar_t__ V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_MAX_BYTES ; 
 scalar_t__ V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_MAX_MB ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5p_mfc_set_slice_mode(struct s5p_mfc_ctx *ctx)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	const struct s5p_mfc_regs *mfc_regs = dev->mfc_regs;

	/* multi-slice control */
	/* multi-slice MB number or bit size */
	writel(ctx->slice_mode, mfc_regs->e_mslice_mode);
	if (ctx->slice_mode == V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_MAX_MB) {
		writel(ctx->slice_size.mb, mfc_regs->e_mslice_size_mb);
	} else if (ctx->slice_mode ==
			V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_MAX_BYTES) {
		writel(ctx->slice_size.bits, mfc_regs->e_mslice_size_bits);
	} else {
		writel(0x0, mfc_regs->e_mslice_size_mb);
		writel(0x0, mfc_regs->e_mslice_size_bits);
	}

	return 0;
}