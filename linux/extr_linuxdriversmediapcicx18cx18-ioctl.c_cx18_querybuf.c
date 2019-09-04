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
struct v4l2_buffer {int dummy; } ;
struct file {struct cx18_open_id* private_data; } ;
struct cx18_stream {scalar_t__ vb_type; } ;
struct cx18_open_id {size_t type; struct cx18* cx; } ;
struct cx18 {struct cx18_stream* streams; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VBI_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  cx18_vb_queue (struct cx18_open_id*) ; 
 int videobuf_querybuf (int /*<<< orphan*/ ,struct v4l2_buffer*) ; 

__attribute__((used)) static int cx18_querybuf(struct file *file, void *priv,
	struct v4l2_buffer *b)
{
	struct cx18_open_id *id = file->private_data;
	struct cx18 *cx = id->cx;
	struct cx18_stream *s = &cx->streams[id->type];

	if ((s->vb_type != V4L2_BUF_TYPE_VIDEO_CAPTURE) &&
		(s->vb_type != V4L2_BUF_TYPE_VBI_CAPTURE))
		return -EINVAL;

	return videobuf_querybuf(cx18_vb_queue(id), b);
}