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
struct v4l2_pix_format {int width; int height; int field; scalar_t__ bytesperline; int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_2__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct solo_enc_dev {struct solo_dev* solo_dev; } ;
struct solo_dev {int video_hsize; int video_vsize; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FRAME_BUF_SIZE ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
#define  V4L2_FIELD_ANY 130 
#define  V4L2_FIELD_INTERLACED 129 
#define  V4L2_FIELD_NONE 128 
 scalar_t__ solo_valid_pixfmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct solo_enc_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int solo_enc_try_fmt_cap(struct file *file, void *priv,
			    struct v4l2_format *f)
{
	struct solo_enc_dev *solo_enc = video_drvdata(file);
	struct solo_dev *solo_dev = solo_enc->solo_dev;
	struct v4l2_pix_format *pix = &f->fmt.pix;

	if (solo_valid_pixfmt(pix->pixelformat, solo_dev->type))
		return -EINVAL;

	if (pix->width < solo_dev->video_hsize ||
	    pix->height < solo_dev->video_vsize << 1) {
		/* Default to CIF 1/2 size */
		pix->width = solo_dev->video_hsize >> 1;
		pix->height = solo_dev->video_vsize;
	} else {
		/* Full frame */
		pix->width = solo_dev->video_hsize;
		pix->height = solo_dev->video_vsize << 1;
	}

	switch (pix->field) {
	case V4L2_FIELD_NONE:
	case V4L2_FIELD_INTERLACED:
		break;
	case V4L2_FIELD_ANY:
	default:
		pix->field = V4L2_FIELD_INTERLACED;
		break;
	}

	/* Just set these */
	pix->colorspace = V4L2_COLORSPACE_SMPTE170M;
	pix->sizeimage = FRAME_BUF_SIZE;
	pix->bytesperline = 0;

	return 0;
}