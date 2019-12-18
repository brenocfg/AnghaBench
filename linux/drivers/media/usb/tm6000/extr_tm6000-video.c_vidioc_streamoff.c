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
struct tm6000_fh {scalar_t__ type; int /*<<< orphan*/  vb_vidq; struct tm6000_core* dev; } ;
struct tm6000_core {int dummy; } ;
struct file {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  res_free (struct tm6000_core*,struct tm6000_fh*) ; 
 int /*<<< orphan*/  videobuf_streamoff (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vidioc_streamoff(struct file *file, void *priv, enum v4l2_buf_type i)
{
	struct tm6000_fh *fh = priv;
	struct tm6000_core *dev = fh->dev;

	if (fh->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	if (i != fh->type)
		return -EINVAL;

	videobuf_streamoff(&fh->vb_vidq);
	res_free(dev, fh);

	return 0;
}