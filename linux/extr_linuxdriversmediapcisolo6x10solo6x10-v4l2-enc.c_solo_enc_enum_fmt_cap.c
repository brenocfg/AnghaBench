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
struct v4l2_fmtdesc {int index; int /*<<< orphan*/  flags; int /*<<< orphan*/  description; int /*<<< orphan*/  pixelformat; } ;
struct solo_enc_dev {TYPE_1__* solo_dev; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SOLO_DEV_6010 129 
#define  SOLO_DEV_6110 128 
 int /*<<< orphan*/  V4L2_FMT_FLAG_COMPRESSED ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_H264 ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_MJPEG ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_MPEG4 ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 struct solo_enc_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int solo_enc_enum_fmt_cap(struct file *file, void *priv,
				 struct v4l2_fmtdesc *f)
{
	struct solo_enc_dev *solo_enc = video_drvdata(file);
	int dev_type = solo_enc->solo_dev->type;

	switch (f->index) {
	case 0:
		switch (dev_type) {
		case SOLO_DEV_6010:
			f->pixelformat = V4L2_PIX_FMT_MPEG4;
			strcpy(f->description, "MPEG-4 part 2");
			break;
		case SOLO_DEV_6110:
			f->pixelformat = V4L2_PIX_FMT_H264;
			strcpy(f->description, "H.264");
			break;
		}
		break;
	case 1:
		f->pixelformat = V4L2_PIX_FMT_MJPEG;
		strcpy(f->description, "MJPEG");
		break;
	default:
		return -EINVAL;
	}

	f->flags = V4L2_FMT_FLAG_COMPRESSED;

	return 0;
}