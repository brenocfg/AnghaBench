#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vim2m_ctx {int /*<<< orphan*/  quant; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; } ;
struct TYPE_3__ {int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct vim2m_ctx* file2ctx (struct file*) ; 
 int vidioc_s_fmt (struct vim2m_ctx*,struct v4l2_format*) ; 
 int vidioc_try_fmt_vid_out (struct file*,void*,struct v4l2_format*) ; 

__attribute__((used)) static int vidioc_s_fmt_vid_out(struct file *file, void *priv,
				struct v4l2_format *f)
{
	struct vim2m_ctx *ctx = file2ctx(file);
	int ret;

	ret = vidioc_try_fmt_vid_out(file, priv, f);
	if (ret)
		return ret;

	ret = vidioc_s_fmt(file2ctx(file), f);
	if (!ret) {
		ctx->colorspace = f->fmt.pix.colorspace;
		ctx->xfer_func = f->fmt.pix.xfer_func;
		ctx->ycbcr_enc = f->fmt.pix.ycbcr_enc;
		ctx->quant = f->fmt.pix.quantization;
	}
	return ret;
}