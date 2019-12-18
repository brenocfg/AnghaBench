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
struct vb2_queue {int dummy; } ;
struct v4l2_buffer {int flags; int /*<<< orphan*/  index; } ;
struct media_device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int V4L2_BUF_FLAG_REQUEST_FD ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int vb2_core_prepare_buf (struct vb2_queue*,int /*<<< orphan*/ ,struct v4l2_buffer*) ; 
 scalar_t__ vb2_fileio_is_active (struct vb2_queue*) ; 
 int vb2_queue_or_prepare_buf (struct vb2_queue*,struct media_device*,struct v4l2_buffer*,int,int /*<<< orphan*/ *) ; 

int vb2_prepare_buf(struct vb2_queue *q, struct media_device *mdev,
		    struct v4l2_buffer *b)
{
	int ret;

	if (vb2_fileio_is_active(q)) {
		dprintk(1, "file io in progress\n");
		return -EBUSY;
	}

	if (b->flags & V4L2_BUF_FLAG_REQUEST_FD)
		return -EINVAL;

	ret = vb2_queue_or_prepare_buf(q, mdev, b, true, NULL);

	return ret ? ret : vb2_core_prepare_buf(q, b->index, b);
}