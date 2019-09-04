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
struct vb2_queue {scalar_t__ type; } ;
struct v4l2_buffer {scalar_t__ type; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_DONE ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int vb2_core_dqbuf (struct vb2_queue*,int /*<<< orphan*/ *,struct v4l2_buffer*,int) ; 
 scalar_t__ vb2_fileio_is_active (struct vb2_queue*) ; 

int vb2_dqbuf(struct vb2_queue *q, struct v4l2_buffer *b, bool nonblocking)
{
	int ret;

	if (vb2_fileio_is_active(q)) {
		dprintk(1, "file io in progress\n");
		return -EBUSY;
	}

	if (b->type != q->type) {
		dprintk(1, "invalid buffer type\n");
		return -EINVAL;
	}

	ret = vb2_core_dqbuf(q, NULL, b, nonblocking);

	/*
	 *  After calling the VIDIOC_DQBUF V4L2_BUF_FLAG_DONE must be
	 *  cleared.
	 */
	b->flags &= ~V4L2_BUF_FLAG_DONE;

	return ret;
}