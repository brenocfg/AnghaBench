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
struct TYPE_4__ {int /*<<< orphan*/  field; } ;
struct viu_fh {int /*<<< orphan*/  type; TYPE_1__ vb_vidq; int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  fmt; } ;
struct TYPE_5__ {int /*<<< orphan*/  field; int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_6__ {TYPE_2__ pix; } ;
struct v4l2_format {int /*<<< orphan*/  type; TYPE_3__ fmt; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  format_by_fourcc (int /*<<< orphan*/ ) ; 
 int vidioc_try_fmt_cap (struct file*,struct viu_fh*,struct v4l2_format*) ; 

__attribute__((used)) static int vidioc_s_fmt_cap(struct file *file, void *priv,
					struct v4l2_format *f)
{
	struct viu_fh *fh = priv;
	int ret;

	ret = vidioc_try_fmt_cap(file, fh, f);
	if (ret < 0)
		return ret;

	fh->fmt           = format_by_fourcc(f->fmt.pix.pixelformat);
	fh->width         = f->fmt.pix.width;
	fh->height        = f->fmt.pix.height;
	fh->sizeimage     = f->fmt.pix.sizeimage;
	fh->vb_vidq.field = f->fmt.pix.field;
	fh->type          = f->type;
	return 0;
}