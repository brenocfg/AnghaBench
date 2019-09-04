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
struct v4l2_buffer {scalar_t__ type; } ;
struct saa7146_fh {int /*<<< orphan*/  vbi_q; int /*<<< orphan*/  video_q; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VBI_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int videobuf_querybuf (int /*<<< orphan*/ *,struct v4l2_buffer*) ; 

__attribute__((used)) static int vidioc_querybuf(struct file *file, void *__fh, struct v4l2_buffer *buf)
{
	struct saa7146_fh *fh = __fh;

	if (buf->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return videobuf_querybuf(&fh->video_q, buf);
	if (buf->type == V4L2_BUF_TYPE_VBI_CAPTURE)
		return videobuf_querybuf(&fh->vbi_q, buf);
	return -EINVAL;
}