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
struct vb2_queue {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  pix; } ;
struct v4l2_format {TYPE_1__ fmt; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;
struct cedrus_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  m2m_ctx; } ;
struct cedrus_ctx {int /*<<< orphan*/  dst_fmt; TYPE_2__ fh; struct cedrus_dev* dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  cedrus_dst_format_set (struct cedrus_dev*,int /*<<< orphan*/ *) ; 
 struct cedrus_ctx* cedrus_file2ctx (struct file*) ; 
 int cedrus_try_fmt_vid_cap (struct file*,void*,struct v4l2_format*) ; 
 struct vb2_queue* v4l2_m2m_get_vq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_is_busy (struct vb2_queue*) ; 

__attribute__((used)) static int cedrus_s_fmt_vid_cap(struct file *file, void *priv,
				struct v4l2_format *f)
{
	struct cedrus_ctx *ctx = cedrus_file2ctx(file);
	struct cedrus_dev *dev = ctx->dev;
	struct vb2_queue *vq;
	int ret;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (vb2_is_busy(vq))
		return -EBUSY;

	ret = cedrus_try_fmt_vid_cap(file, priv, f);
	if (ret)
		return ret;

	ctx->dst_fmt = f->fmt.pix;

	cedrus_dst_format_set(dev, &ctx->dst_fmt);

	return 0;
}