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
struct TYPE_4__ {scalar_t__ clipcount; int /*<<< orphan*/ * clips; } ;
struct TYPE_3__ {TYPE_2__ win; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct saa7134_dev {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ saa7134_no_overlay ; 
 int verify_preview (struct saa7134_dev*,TYPE_2__*,int) ; 
 struct saa7134_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int saa7134_try_fmt_vid_overlay(struct file *file, void *priv,
						struct v4l2_format *f)
{
	struct saa7134_dev *dev = video_drvdata(file);

	if (saa7134_no_overlay > 0) {
		pr_err("V4L2_BUF_TYPE_VIDEO_OVERLAY: no_overlay\n");
		return -EINVAL;
	}

	if (f->fmt.win.clips == NULL)
		f->fmt.win.clipcount = 0;
	return verify_preview(dev, &f->fmt.win, true);
}