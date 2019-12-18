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
struct v4l2_pix_format_mplane {int /*<<< orphan*/  width; } ;
struct hantro_dev {int dummy; } ;
struct hantro_ctx {TYPE_1__* vpu_src_fmt; struct v4l2_pix_format_mplane src_fmt; } ;
struct TYPE_2__ {int /*<<< orphan*/  enc_fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  H1_REG_IN_IMG_CTRL ; 
 int H1_REG_IN_IMG_CTRL_FMT (int /*<<< orphan*/ ) ; 
 int H1_REG_IN_IMG_CTRL_OVRFLB_D4 (int /*<<< orphan*/ ) ; 
 int H1_REG_IN_IMG_CTRL_OVRFLR_D4 (int /*<<< orphan*/ ) ; 
 int H1_REG_IN_IMG_CTRL_ROW_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vepu_write_relaxed (struct hantro_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hantro_h1_set_src_img_ctrl(struct hantro_dev *vpu,
				       struct hantro_ctx *ctx)
{
	struct v4l2_pix_format_mplane *pix_fmt = &ctx->src_fmt;
	u32 reg;

	reg = H1_REG_IN_IMG_CTRL_ROW_LEN(pix_fmt->width)
		| H1_REG_IN_IMG_CTRL_OVRFLR_D4(0)
		| H1_REG_IN_IMG_CTRL_OVRFLB_D4(0)
		| H1_REG_IN_IMG_CTRL_FMT(ctx->vpu_src_fmt->enc_fmt);
	vepu_write_relaxed(vpu, reg, H1_REG_IN_IMG_CTRL);
}