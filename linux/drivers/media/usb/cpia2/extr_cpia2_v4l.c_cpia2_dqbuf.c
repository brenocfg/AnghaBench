#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ offset; } ;
struct v4l2_buffer {scalar_t__ type; scalar_t__ memory; int index; int flags; int /*<<< orphan*/  bytesused; int /*<<< orphan*/  sequence; int /*<<< orphan*/  timecode; scalar_t__ request_fd; scalar_t__ reserved2; int /*<<< orphan*/  length; TYPE_1__ m; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  field; } ;
struct framebuf {scalar_t__ status; int num; } ;
struct file {int f_flags; } ;
struct camera_data {TYPE_2__* buffers; int /*<<< orphan*/  frame_size; scalar_t__ frame_buffer; int /*<<< orphan*/  vdev; int /*<<< orphan*/  v4l2_lock; struct framebuf* curbuff; int /*<<< orphan*/  wq_stream; } ;
struct TYPE_4__ {int /*<<< orphan*/  status; scalar_t__ data; int /*<<< orphan*/  seq; int /*<<< orphan*/  ts; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENOTTY ; 
 int ERESTARTSYS ; 
 scalar_t__ FRAME_READY ; 
 int O_NONBLOCK ; 
 int V4L2_BUF_FLAG_DONE ; 
 int V4L2_BUF_FLAG_MAPPED ; 
 int V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 scalar_t__ V4L2_MEMORY_MMAP ; 
 int /*<<< orphan*/  current ; 
 int find_earliest_filled_buffer (struct camera_data*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ns_to_timeval (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 struct camera_data* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  video_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cpia2_dqbuf(struct file *file, void *fh, struct v4l2_buffer *buf)
{
	struct camera_data *cam = video_drvdata(file);
	int frame;

	if(buf->type != V4L2_BUF_TYPE_VIDEO_CAPTURE ||
	   buf->memory != V4L2_MEMORY_MMAP)
		return -EINVAL;

	frame = find_earliest_filled_buffer(cam);

	if(frame < 0 && file->f_flags&O_NONBLOCK)
		return -EAGAIN;

	if(frame < 0) {
		/* Wait for a frame to become available */
		struct framebuf *cb=cam->curbuff;
		mutex_unlock(&cam->v4l2_lock);
		wait_event_interruptible(cam->wq_stream,
					 !video_is_registered(&cam->vdev) ||
					 (cb=cam->curbuff)->status == FRAME_READY);
		mutex_lock(&cam->v4l2_lock);
		if (signal_pending(current))
			return -ERESTARTSYS;
		if (!video_is_registered(&cam->vdev))
			return -ENOTTY;
		frame = cb->num;
	}


	buf->index = frame;
	buf->bytesused = cam->buffers[buf->index].length;
	buf->flags = V4L2_BUF_FLAG_MAPPED | V4L2_BUF_FLAG_DONE
		| V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	buf->field = V4L2_FIELD_NONE;
	buf->timestamp = ns_to_timeval(cam->buffers[buf->index].ts);
	buf->sequence = cam->buffers[buf->index].seq;
	buf->m.offset = cam->buffers[buf->index].data - cam->frame_buffer;
	buf->length = cam->frame_size;
	buf->reserved2 = 0;
	buf->request_fd = 0;
	memset(&buf->timecode, 0, sizeof(buf->timecode));

	DBG("DQBUF #%d status:%d seq:%d length:%d\n", buf->index,
	    cam->buffers[buf->index].status, buf->sequence, buf->bytesused);

	return 0;
}