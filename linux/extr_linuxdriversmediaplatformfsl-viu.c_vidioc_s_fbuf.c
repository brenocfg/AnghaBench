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
struct viu_fmt {int depth; } ;
struct viu_fh {struct viu_dev* dev; } ;
struct TYPE_2__ {int bytesperline; int width; int /*<<< orphan*/  pixelformat; } ;
struct v4l2_framebuffer {TYPE_1__ fmt; } ;
struct viu_dev {struct v4l2_framebuffer ovbuf; struct viu_fmt* ovfmt; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  CAP_SYS_RAWIO ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct viu_fmt* format_by_fourcc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_s_fbuf(struct file *file, void *priv, const struct v4l2_framebuffer *arg)
{
	struct viu_fh  *fh = priv;
	struct viu_dev *dev = fh->dev;
	const struct v4l2_framebuffer *fb = arg;
	struct viu_fmt *fmt;

	if (!capable(CAP_SYS_ADMIN) && !capable(CAP_SYS_RAWIO))
		return -EPERM;

	/* check args */
	fmt = format_by_fourcc(fb->fmt.pixelformat);
	if (fmt == NULL)
		return -EINVAL;

	/* ok, accept it */
	dev->ovbuf = *fb;
	dev->ovfmt = fmt;
	if (dev->ovbuf.fmt.bytesperline == 0) {
		dev->ovbuf.fmt.bytesperline =
			dev->ovbuf.fmt.width * fmt->depth / 8;
	}
	return 0;
}