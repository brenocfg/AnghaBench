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
struct TYPE_8__ {int field; int height; int width; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_7__ {TYPE_4__ pix; } ;
struct v4l2_format {TYPE_3__ fmt; } ;
struct file {int dummy; } ;
struct bttv_format {int flags; } ;
struct bttv_fh {int /*<<< orphan*/  do_crop; struct bttv* btv; } ;
struct bttv {TYPE_2__* crop; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;
typedef  int __s32 ;
struct TYPE_5__ {int height; } ;
struct TYPE_6__ {TYPE_1__ rect; } ;

/* Variables and functions */
 int EINVAL ; 
 int FORMAT_FLAGS_PLANAR ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
#define  V4L2_FIELD_ALTERNATE 133 
#define  V4L2_FIELD_BOTTOM 132 
#define  V4L2_FIELD_INTERLACED 131 
#define  V4L2_FIELD_SEQ_BT 130 
#define  V4L2_FIELD_SEQ_TB 129 
#define  V4L2_FIELD_TOP 128 
 int /*<<< orphan*/  bttv_get_width_mask_vid_cap (struct bttv_format const*,unsigned int*,unsigned int*) ; 
 struct bttv_format* format_by_fourcc (int /*<<< orphan*/ ) ; 
 int limit_scaled_size_lock (struct bttv_fh*,int*,int*,int,unsigned int,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pix_format_set_size (TYPE_4__*,struct bttv_format const*,int,int) ; 

__attribute__((used)) static int bttv_try_fmt_vid_cap(struct file *file, void *priv,
						struct v4l2_format *f)
{
	const struct bttv_format *fmt;
	struct bttv_fh *fh = priv;
	struct bttv *btv = fh->btv;
	enum v4l2_field field;
	__s32 width, height;
	__s32 height2;
	unsigned int width_mask, width_bias;
	int rc;

	fmt = format_by_fourcc(f->fmt.pix.pixelformat);
	if (NULL == fmt)
		return -EINVAL;

	field = f->fmt.pix.field;

	switch (field) {
	case V4L2_FIELD_TOP:
	case V4L2_FIELD_BOTTOM:
	case V4L2_FIELD_ALTERNATE:
	case V4L2_FIELD_INTERLACED:
		break;
	case V4L2_FIELD_SEQ_BT:
	case V4L2_FIELD_SEQ_TB:
		if (!(fmt->flags & FORMAT_FLAGS_PLANAR)) {
			field = V4L2_FIELD_SEQ_TB;
			break;
		}
		/* fall through */
	default: /* FIELD_ANY case */
		height2 = btv->crop[!!fh->do_crop].rect.height >> 1;
		field = (f->fmt.pix.height > height2)
			? V4L2_FIELD_INTERLACED
			: V4L2_FIELD_BOTTOM;
		break;
	}

	width = f->fmt.pix.width;
	height = f->fmt.pix.height;

	bttv_get_width_mask_vid_cap(fmt, &width_mask, &width_bias);
	rc = limit_scaled_size_lock(fh, &width, &height, field,
			       width_mask, width_bias,
			       /* adjust_size */ 1,
			       /* adjust_crop */ 0);
	if (0 != rc)
		return rc;

	/* update data for the application */
	f->fmt.pix.field = field;
	pix_format_set_size(&f->fmt.pix, fmt, width, height);
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;

	return 0;
}