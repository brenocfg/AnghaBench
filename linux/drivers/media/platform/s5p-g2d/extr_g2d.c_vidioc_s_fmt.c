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
struct vb2_queue {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  bytesperline; int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_6__ {TYPE_2__ pix; } ;
struct v4l2_format {TYPE_3__ fmt; int /*<<< orphan*/  type; } ;
struct g2d_frame {int /*<<< orphan*/  stride; struct g2d_fmt* fmt; int /*<<< orphan*/  height; int /*<<< orphan*/  bottom; int /*<<< orphan*/  width; int /*<<< orphan*/  right; int /*<<< orphan*/  c_height; int /*<<< orphan*/  c_width; scalar_t__ o_height; scalar_t__ o_width; int /*<<< orphan*/  size; } ;
struct g2d_fmt {int dummy; } ;
struct g2d_dev {int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  m2m_ctx; } ;
struct g2d_ctx {TYPE_1__ fh; struct g2d_dev* dev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct g2d_frame*) ; 
 int PTR_ERR (struct g2d_frame*) ; 
 struct g2d_fmt* find_fmt (struct v4l2_format*) ; 
 struct g2d_frame* get_frame (struct g2d_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct vb2_queue* v4l2_m2m_get_vq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_is_busy (struct vb2_queue*) ; 
 int vidioc_try_fmt (struct file*,void*,struct v4l2_format*) ; 

__attribute__((used)) static int vidioc_s_fmt(struct file *file, void *prv, struct v4l2_format *f)
{
	struct g2d_ctx *ctx = prv;
	struct g2d_dev *dev = ctx->dev;
	struct vb2_queue *vq;
	struct g2d_frame *frm;
	struct g2d_fmt *fmt;
	int ret = 0;

	/* Adjust all values accordingly to the hardware capabilities
	 * and chosen format. */
	ret = vidioc_try_fmt(file, prv, f);
	if (ret)
		return ret;
	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (vb2_is_busy(vq)) {
		v4l2_err(&dev->v4l2_dev, "queue (%d) bust\n", f->type);
		return -EBUSY;
	}
	frm = get_frame(ctx, f->type);
	if (IS_ERR(frm))
		return PTR_ERR(frm);
	fmt = find_fmt(f);
	if (!fmt)
		return -EINVAL;
	frm->width	= f->fmt.pix.width;
	frm->height	= f->fmt.pix.height;
	frm->size	= f->fmt.pix.sizeimage;
	/* Reset crop settings */
	frm->o_width	= 0;
	frm->o_height	= 0;
	frm->c_width	= frm->width;
	frm->c_height	= frm->height;
	frm->right	= frm->width;
	frm->bottom	= frm->height;
	frm->fmt	= fmt;
	frm->stride	= f->fmt.pix.bytesperline;
	return 0;
}