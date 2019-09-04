#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  timestamp; struct vb2_queue* vb2_queue; } ;
struct vb2_v4l2_buffer {TYPE_1__ vb2_buf; int /*<<< orphan*/  field; scalar_t__ sequence; } ;
struct vb2_queue {scalar_t__ type; } ;
struct au0828_dmaqueue {int dummy; } ;
struct au0828_dev {int /*<<< orphan*/  vbi_frame_count; int /*<<< orphan*/  frame_count; } ;
struct au0828_buffer {int /*<<< orphan*/  top_field; struct vb2_v4l2_buffer vb; } ;

/* Variables and functions */
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  au0828_isocdbg (char*,struct au0828_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  vb2_buffer_done (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void buffer_filled(struct au0828_dev *dev,
				 struct au0828_dmaqueue *dma_q,
				 struct au0828_buffer *buf)
{
	struct vb2_v4l2_buffer *vb = &buf->vb;
	struct vb2_queue *q = vb->vb2_buf.vb2_queue;

	/* Advice that buffer was filled */
	au0828_isocdbg("[%p/%d] wakeup\n", buf, buf->top_field);

	if (q->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		vb->sequence = dev->frame_count++;
	else
		vb->sequence = dev->vbi_frame_count++;

	vb->field = V4L2_FIELD_INTERLACED;
	vb->vb2_buf.timestamp = ktime_get_ns();
	vb2_buffer_done(&vb->vb2_buf, VB2_BUF_STATE_DONE);
}