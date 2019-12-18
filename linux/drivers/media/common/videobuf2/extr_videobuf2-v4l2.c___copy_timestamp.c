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
struct vb2_v4l2_buffer {int flags; int /*<<< orphan*/  timecode; } ;
struct vb2_queue {scalar_t__ copy_timestamp; scalar_t__ is_output; } ;
struct vb2_buffer {int /*<<< orphan*/  timestamp; struct vb2_queue* vb2_queue; } ;
struct v4l2_buffer {int flags; int /*<<< orphan*/  timecode; int /*<<< orphan*/  timestamp; } ;

/* Variables and functions */
 int V4L2_BUF_FLAG_TIMECODE ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 int /*<<< orphan*/  v4l2_timeval_to_ns (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __copy_timestamp(struct vb2_buffer *vb, const void *pb)
{
	const struct v4l2_buffer *b = pb;
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct vb2_queue *q = vb->vb2_queue;

	if (q->is_output) {
		/*
		 * For output buffers copy the timestamp if needed,
		 * and the timecode field and flag if needed.
		 */
		if (q->copy_timestamp)
			vb->timestamp = v4l2_timeval_to_ns(&b->timestamp);
		vbuf->flags |= b->flags & V4L2_BUF_FLAG_TIMECODE;
		if (b->flags & V4L2_BUF_FLAG_TIMECODE)
			vbuf->timecode = b->timecode;
	}
}