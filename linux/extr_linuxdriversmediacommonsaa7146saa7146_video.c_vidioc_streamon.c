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
struct saa7146_fh {int /*<<< orphan*/  vbi_q; int /*<<< orphan*/  video_q; } ;
struct file {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_D (char*,int) ; 
 int EINVAL ; 
 int V4L2_BUF_TYPE_VBI_CAPTURE ; 
 int V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int video_begin (struct saa7146_fh*) ; 
 int videobuf_streamon (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vidioc_streamon(struct file *file, void *__fh, enum v4l2_buf_type type)
{
	struct saa7146_fh *fh = __fh;
	int err;

	DEB_D("VIDIOC_STREAMON, type:%d\n", type);

	err = video_begin(fh);
	if (err)
		return err;
	if (type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return videobuf_streamon(&fh->video_q);
	if (type == V4L2_BUF_TYPE_VBI_CAPTURE)
		return videobuf_streamon(&fh->vbi_q);
	return -EINVAL;
}