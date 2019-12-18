#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_8__ {TYPE_3__ pix; } ;
struct v4l2_format {TYPE_4__ fmt; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;
struct bttv_format {int dummy; } ;
struct TYPE_5__ {int field; int /*<<< orphan*/  last; } ;
struct bttv_fh {int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__ cap; struct bttv_format const* fmt; struct bttv* btv; } ;
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; struct bttv_format const* fmt; } ;
struct bttv {TYPE_2__ init; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;
typedef  int /*<<< orphan*/  __s32 ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  bttv_get_width_mask_vid_cap (struct bttv_format const*,unsigned int*,unsigned int*) ; 
 int bttv_switch_type (struct bttv_fh*,int /*<<< orphan*/ ) ; 
 int bttv_try_fmt_vid_cap (struct file*,void*,struct v4l2_format*) ; 
 struct bttv_format* format_by_fourcc (int /*<<< orphan*/ ) ; 
 int limit_scaled_size_lock (struct bttv_fh*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,unsigned int,unsigned int,int,int) ; 

__attribute__((used)) static int bttv_s_fmt_vid_cap(struct file *file, void *priv,
				struct v4l2_format *f)
{
	int retval;
	const struct bttv_format *fmt;
	struct bttv_fh *fh = priv;
	struct bttv *btv = fh->btv;
	__s32 width, height;
	unsigned int width_mask, width_bias;
	enum v4l2_field field;

	retval = bttv_switch_type(fh, f->type);
	if (0 != retval)
		return retval;

	retval = bttv_try_fmt_vid_cap(file, priv, f);
	if (0 != retval)
		return retval;

	width = f->fmt.pix.width;
	height = f->fmt.pix.height;
	field = f->fmt.pix.field;

	fmt = format_by_fourcc(f->fmt.pix.pixelformat);
	bttv_get_width_mask_vid_cap(fmt, &width_mask, &width_bias);
	retval = limit_scaled_size_lock(fh, &width, &height, f->fmt.pix.field,
			       width_mask, width_bias,
			       /* adjust_size */ 1,
			       /* adjust_crop */ 1);
	if (0 != retval)
		return retval;

	f->fmt.pix.field = field;

	/* update our state information */
	fh->fmt              = fmt;
	fh->cap.field        = f->fmt.pix.field;
	fh->cap.last         = V4L2_FIELD_NONE;
	fh->width            = f->fmt.pix.width;
	fh->height           = f->fmt.pix.height;
	btv->init.fmt        = fmt;
	btv->init.width      = f->fmt.pix.width;
	btv->init.height     = f->fmt.pix.height;

	return 0;
}