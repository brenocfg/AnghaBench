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
struct v4l2_buffer {scalar_t__ memory; scalar_t__ index; int flags; } ;
struct stk_sio_buffer {struct v4l2_buffer v4lbuf; int /*<<< orphan*/  list; } ;
struct stk_camera {scalar_t__ n_sbufs; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  sio_avail; struct stk_sio_buffer* sio_bufs; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int V4L2_BUF_FLAG_DONE ; 
 int V4L2_BUF_FLAG_QUEUED ; 
 scalar_t__ V4L2_MEMORY_MMAP ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct stk_camera* video_drvdata (struct file*) ; 

__attribute__((used)) static int stk_vidioc_qbuf(struct file *filp,
		void *priv, struct v4l2_buffer *buf)
{
	struct stk_camera *dev = video_drvdata(filp);
	struct stk_sio_buffer *sbuf;
	unsigned long flags;

	if (buf->memory != V4L2_MEMORY_MMAP)
		return -EINVAL;

	if (buf->index >= dev->n_sbufs)
		return -EINVAL;
	sbuf = dev->sio_bufs + buf->index;
	if (sbuf->v4lbuf.flags & V4L2_BUF_FLAG_QUEUED)
		return 0;
	sbuf->v4lbuf.flags |= V4L2_BUF_FLAG_QUEUED;
	sbuf->v4lbuf.flags &= ~V4L2_BUF_FLAG_DONE;
	spin_lock_irqsave(&dev->spinlock, flags);
	list_add_tail(&sbuf->list, &dev->sio_avail);
	*buf = sbuf->v4lbuf;
	spin_unlock_irqrestore(&dev->spinlock, flags);
	return 0;
}