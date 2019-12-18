#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct viu_fh {struct viu_dev* dev; } ;
struct v4l2_framebuffer {int /*<<< orphan*/  capability; } ;
struct viu_dev {struct v4l2_framebuffer ovbuf; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_FBUF_CAP_LIST_CLIPPING ; 

__attribute__((used)) static int vidioc_g_fbuf(struct file *file, void *priv, struct v4l2_framebuffer *arg)
{
	struct viu_fh  *fh = priv;
	struct viu_dev *dev = fh->dev;
	struct v4l2_framebuffer *fb = arg;

	*fb = dev->ovbuf;
	fb->capability = V4L2_FBUF_CAP_LIST_CLIPPING;
	return 0;
}