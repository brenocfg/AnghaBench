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
struct TYPE_4__ {scalar_t__ offset; } ;
struct v4l2_buffer {scalar_t__ type; size_t index; int /*<<< orphan*/  bytesused; int /*<<< orphan*/  sequence; int /*<<< orphan*/  flags; TYPE_2__ m; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  memory; int /*<<< orphan*/  length; } ;
struct file {int dummy; } ;
struct camera_data {size_t num_frames; TYPE_1__* buffers; scalar_t__ mmapped; int /*<<< orphan*/  frame_size; scalar_t__ frame_buffer; } ;
struct TYPE_3__ {int status; int /*<<< orphan*/  seq; int /*<<< orphan*/  ts; int /*<<< orphan*/  length; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,size_t,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  FRAME_EMPTY 131 
#define  FRAME_ERROR 130 
#define  FRAME_READING 129 
#define  FRAME_READY 128 
 int /*<<< orphan*/  V4L2_BUF_FLAG_DONE ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_MAPPED ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_QUEUED ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_MEMORY_MMAP ; 
 int /*<<< orphan*/  ns_to_timeval (int /*<<< orphan*/ ) ; 
 struct camera_data* video_drvdata (struct file*) ; 

__attribute__((used)) static int cpia2_querybuf(struct file *file, void *fh, struct v4l2_buffer *buf)
{
	struct camera_data *cam = video_drvdata(file);

	if(buf->type != V4L2_BUF_TYPE_VIDEO_CAPTURE ||
	   buf->index >= cam->num_frames)
		return -EINVAL;

	buf->m.offset = cam->buffers[buf->index].data - cam->frame_buffer;
	buf->length = cam->frame_size;

	buf->memory = V4L2_MEMORY_MMAP;

	if(cam->mmapped)
		buf->flags = V4L2_BUF_FLAG_MAPPED;
	else
		buf->flags = 0;

	buf->flags |= V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;

	switch (cam->buffers[buf->index].status) {
	case FRAME_EMPTY:
	case FRAME_ERROR:
	case FRAME_READING:
		buf->bytesused = 0;
		buf->flags = V4L2_BUF_FLAG_QUEUED;
		break;
	case FRAME_READY:
		buf->bytesused = cam->buffers[buf->index].length;
		buf->timestamp = ns_to_timeval(cam->buffers[buf->index].ts);
		buf->sequence = cam->buffers[buf->index].seq;
		buf->flags = V4L2_BUF_FLAG_DONE;
		break;
	}

	DBG("QUERYBUF index:%d offset:%d flags:%d seq:%d bytesused:%d\n",
	     buf->index, buf->m.offset, buf->flags, buf->sequence,
	     buf->bytesused);

	return 0;
}