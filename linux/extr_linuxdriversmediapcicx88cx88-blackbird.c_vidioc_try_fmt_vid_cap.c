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
struct TYPE_3__ {int sizeimage; int field; unsigned int height; int /*<<< orphan*/  width; int /*<<< orphan*/  colorspace; scalar_t__ bytesperline; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct file {int dummy; } ;
struct cx88_core {int /*<<< orphan*/  tvnorm; } ;
struct cx8802_dev {int ts_packet_size; int ts_packet_count; struct cx88_core* core; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
#define  V4L2_FIELD_BOTTOM 132 
 scalar_t__ V4L2_FIELD_HAS_T_OR_B (int) ; 
#define  V4L2_FIELD_INTERLACED 131 
#define  V4L2_FIELD_SEQ_BT 130 
#define  V4L2_FIELD_SEQ_TB 129 
#define  V4L2_FIELD_TOP 128 
 int /*<<< orphan*/  V4L2_PIX_FMT_MPEG ; 
 unsigned int norm_maxh (int /*<<< orphan*/ ) ; 
 unsigned int norm_maxw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l_bound_align_image (int /*<<< orphan*/ *,int,unsigned int,int,unsigned int*,int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cx8802_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_try_fmt_vid_cap(struct file *file, void *priv,
				  struct v4l2_format *f)
{
	struct cx8802_dev *dev = video_drvdata(file);
	struct cx88_core *core = dev->core;
	unsigned int maxw, maxh;
	enum v4l2_field field;

	f->fmt.pix.pixelformat  = V4L2_PIX_FMT_MPEG;
	f->fmt.pix.bytesperline = 0;
	f->fmt.pix.sizeimage    = dev->ts_packet_size * dev->ts_packet_count;
	f->fmt.pix.colorspace   = V4L2_COLORSPACE_SMPTE170M;

	maxw = norm_maxw(core->tvnorm);
	maxh = norm_maxh(core->tvnorm);

	field = f->fmt.pix.field;

	switch (field) {
	case V4L2_FIELD_TOP:
	case V4L2_FIELD_BOTTOM:
	case V4L2_FIELD_INTERLACED:
	case V4L2_FIELD_SEQ_BT:
	case V4L2_FIELD_SEQ_TB:
		break;
	default:
		field = (f->fmt.pix.height > maxh / 2)
			? V4L2_FIELD_INTERLACED
			: V4L2_FIELD_BOTTOM;
		break;
	}
	if (V4L2_FIELD_HAS_T_OR_B(field))
		maxh /= 2;

	v4l_bound_align_image(&f->fmt.pix.width, 48, maxw, 2,
			      &f->fmt.pix.height, 32, maxh, 0, 0);
	f->fmt.pix.field = field;
	return 0;
}