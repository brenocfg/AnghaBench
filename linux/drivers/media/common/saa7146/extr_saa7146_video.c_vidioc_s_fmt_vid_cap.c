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
struct TYPE_4__ {int /*<<< orphan*/  pixelformat; } ;
struct TYPE_3__ {TYPE_2__ pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct saa7146_vv {TYPE_2__ video_fmt; } ;
struct saa7146_fh {struct saa7146_dev* dev; } ;
struct saa7146_dev {struct saa7146_vv* vv_data; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_EE (char*,...) ; 
 int EBUSY ; 
 scalar_t__ IS_CAPTURE_ACTIVE (struct saa7146_fh*) ; 
 int vidioc_try_fmt_vid_cap (struct file*,struct saa7146_fh*,struct v4l2_format*) ; 

__attribute__((used)) static int vidioc_s_fmt_vid_cap(struct file *file, void *__fh, struct v4l2_format *f)
{
	struct saa7146_fh *fh = __fh;
	struct saa7146_dev *dev = fh->dev;
	struct saa7146_vv *vv = dev->vv_data;
	int err;

	DEB_EE("V4L2_BUF_TYPE_VIDEO_CAPTURE: dev:%p, fh:%p\n", dev, fh);
	if (IS_CAPTURE_ACTIVE(fh) != 0) {
		DEB_EE("streaming capture is active\n");
		return -EBUSY;
	}
	err = vidioc_try_fmt_vid_cap(file, fh, f);
	if (0 != err)
		return err;
	vv->video_fmt = f->fmt.pix;
	DEB_EE("set to pixelformat '%4.4s'\n",
	       (char *)&vv->video_fmt.pixelformat);
	return 0;
}