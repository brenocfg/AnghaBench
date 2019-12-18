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
struct TYPE_3__ {int width; int height; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  field; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct tw5864_input {int std; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  H264_VLC_BUF_SIZE ; 
#define  STD_NTSC 130 
#define  STD_PAL 129 
#define  STD_SECAM 128 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_H264 ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct tw5864_input* video_drvdata (struct file*) ; 

__attribute__((used)) static int tw5864_fmt_vid_cap(struct file *file, void *priv,
			      struct v4l2_format *f)
{
	struct tw5864_input *input = video_drvdata(file);

	f->fmt.pix.width = 704;
	switch (input->std) {
	default:
		WARN_ON_ONCE(1);
		return -EINVAL;
	case STD_NTSC:
		f->fmt.pix.height = 480;
		break;
	case STD_PAL:
	case STD_SECAM:
		f->fmt.pix.height = 576;
		break;
	}
	f->fmt.pix.field = V4L2_FIELD_INTERLACED;
	f->fmt.pix.pixelformat = V4L2_PIX_FMT_H264;
	f->fmt.pix.sizeimage = H264_VLC_BUF_SIZE;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	return 0;
}