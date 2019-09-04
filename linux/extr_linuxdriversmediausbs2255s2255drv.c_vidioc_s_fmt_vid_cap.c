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
struct TYPE_4__ {scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  field; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_5__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct s2255_mode {scalar_t__ scale; int color; int restart; scalar_t__ format; } ;
struct TYPE_6__ {int capturemode; } ;
struct s2255_vc {scalar_t__ width; scalar_t__ height; int jpegqual; struct s2255_mode mode; struct s2255_fmt const* fmt; TYPE_3__ cap_parm; int /*<<< orphan*/  field; int /*<<< orphan*/  dev; struct vb2_queue vb_vidq; } ;
struct s2255_fmt {int fourcc; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int COLOR_JPG ; 
 int COLOR_Y8 ; 
 int COLOR_YUVPK ; 
 int COLOR_YUVPL ; 
 int EBUSY ; 
 int EINVAL ; 
 int MASK_COLOR ; 
 scalar_t__ SCALE_1CIFS ; 
 scalar_t__ SCALE_2CIFS ; 
 scalar_t__ SCALE_4CIFS ; 
 scalar_t__ SCALE_4CIFSI ; 
 int V4L2_MODE_HIGHQUALITY ; 
#define  V4L2_PIX_FMT_GREY 133 
#define  V4L2_PIX_FMT_JPEG 132 
#define  V4L2_PIX_FMT_MJPEG 131 
#define  V4L2_PIX_FMT_UYVY 130 
#define  V4L2_PIX_FMT_YUV422P 129 
#define  V4L2_PIX_FMT_YUYV 128 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 
 struct s2255_fmt* format_by_fourcc (int /*<<< orphan*/ ) ; 
 scalar_t__ norm_minh (struct s2255_vc*) ; 
 scalar_t__ norm_minw (struct s2255_vc*) ; 
 int /*<<< orphan*/  s2255_set_mode (struct s2255_vc*,struct s2255_mode*) ; 
 scalar_t__ vb2_is_busy (struct vb2_queue*) ; 
 struct s2255_vc* video_drvdata (struct file*) ; 
 int vidioc_try_fmt_vid_cap (struct file*,struct s2255_vc*,struct v4l2_format*) ; 

__attribute__((used)) static int vidioc_s_fmt_vid_cap(struct file *file, void *priv,
			    struct v4l2_format *f)
{
	struct s2255_vc *vc = video_drvdata(file);
	const struct s2255_fmt *fmt;
	struct vb2_queue *q = &vc->vb_vidq;
	struct s2255_mode mode;
	int ret;

	ret = vidioc_try_fmt_vid_cap(file, vc, f);

	if (ret < 0)
		return ret;

	fmt = format_by_fourcc(f->fmt.pix.pixelformat);

	if (fmt == NULL)
		return -EINVAL;

	if (vb2_is_busy(q)) {
		dprintk(vc->dev, 1, "queue busy\n");
		return -EBUSY;
	}

	mode = vc->mode;
	vc->fmt = fmt;
	vc->width = f->fmt.pix.width;
	vc->height = f->fmt.pix.height;
	vc->field = f->fmt.pix.field;
	if (vc->width > norm_minw(vc)) {
		if (vc->height > norm_minh(vc)) {
			if (vc->cap_parm.capturemode &
			    V4L2_MODE_HIGHQUALITY)
				mode.scale = SCALE_4CIFSI;
			else
				mode.scale = SCALE_4CIFS;
		} else
			mode.scale = SCALE_2CIFS;

	} else {
		mode.scale = SCALE_1CIFS;
	}
	/* color mode */
	switch (vc->fmt->fourcc) {
	case V4L2_PIX_FMT_GREY:
		mode.color &= ~MASK_COLOR;
		mode.color |= COLOR_Y8;
		break;
	case V4L2_PIX_FMT_JPEG:
	case V4L2_PIX_FMT_MJPEG:
		mode.color &= ~MASK_COLOR;
		mode.color |= COLOR_JPG;
		mode.color |= (vc->jpegqual << 8);
		break;
	case V4L2_PIX_FMT_YUV422P:
		mode.color &= ~MASK_COLOR;
		mode.color |= COLOR_YUVPL;
		break;
	case V4L2_PIX_FMT_YUYV:
	case V4L2_PIX_FMT_UYVY:
	default:
		mode.color &= ~MASK_COLOR;
		mode.color |= COLOR_YUVPK;
		break;
	}
	if ((mode.color & MASK_COLOR) != (vc->mode.color & MASK_COLOR))
		mode.restart = 1;
	else if (mode.scale != vc->mode.scale)
		mode.restart = 1;
	else if (mode.format != vc->mode.format)
		mode.restart = 1;
	vc->mode = mode;
	(void) s2255_set_mode(vc, &mode);
	return 0;
}