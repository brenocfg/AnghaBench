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
struct TYPE_6__ {int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; } ;
struct TYPE_5__ {TYPE_3__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct pxp_ctx {TYPE_1__* q_data; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  quant; int /*<<< orphan*/  ycbcr_enc; } ;

/* Variables and functions */
 size_t V4L2_M2M_DST ; 
 struct pxp_ctx* file2ctx (struct file*) ; 
 int pxp_s_fmt (struct pxp_ctx*,struct v4l2_format*) ; 
 int pxp_try_fmt_vid_cap (struct file*,void*,struct v4l2_format*) ; 

__attribute__((used)) static int pxp_s_fmt_vid_cap(struct file *file, void *priv,
			     struct v4l2_format *f)
{
	struct pxp_ctx *ctx = file2ctx(file);
	int ret;

	ret = pxp_try_fmt_vid_cap(file, priv, f);
	if (ret)
		return ret;

	ret = pxp_s_fmt(file2ctx(file), f);
	if (ret)
		return ret;

	ctx->q_data[V4L2_M2M_DST].ycbcr_enc = f->fmt.pix.ycbcr_enc;
	ctx->q_data[V4L2_M2M_DST].quant = f->fmt.pix.quantization;

	return 0;
}