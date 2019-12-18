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
struct viu_fh {scalar_t__ type; int /*<<< orphan*/  vb_vidq; int /*<<< orphan*/  dev; } ;
struct file {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int videobuf_streamoff (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  viu_stop_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_streamoff(struct file *file, void *priv, enum v4l2_buf_type i)
{
	struct viu_fh  *fh = priv;

	if (fh->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;
	if (fh->type != i)
		return -EINVAL;

	viu_stop_dma(fh->dev);

	return videobuf_streamoff(&fh->vb_vidq);
}