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
struct TYPE_3__ {int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct tw68_dev {int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  fmt; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  format_by_fourcc (int /*<<< orphan*/ ) ; 
 int tw68_try_fmt_vid_cap (struct file*,void*,struct v4l2_format*) ; 
 struct tw68_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int tw68_s_fmt_vid_cap(struct file *file, void *priv,
					struct v4l2_format *f)
{
	struct tw68_dev *dev = video_drvdata(file);
	int err;

	err = tw68_try_fmt_vid_cap(file, priv, f);
	if (0 != err)
		return err;

	dev->fmt = format_by_fourcc(f->fmt.pix.pixelformat);
	dev->width = f->fmt.pix.width;
	dev->height = f->fmt.pix.height;
	dev->field = f->fmt.pix.field;
	return 0;
}