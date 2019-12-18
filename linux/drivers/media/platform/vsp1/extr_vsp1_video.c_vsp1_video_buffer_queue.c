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
struct vsp1_video {int pipe_index; int /*<<< orphan*/  queue; TYPE_2__* rwpf; int /*<<< orphan*/  irqlock; int /*<<< orphan*/  irqqueue; } ;
struct vsp1_vb2_buffer {int /*<<< orphan*/  mem; int /*<<< orphan*/  queue; } ;
struct vsp1_pipeline {int buffers_ready; int /*<<< orphan*/  irqlock; } ;
struct vb2_v4l2_buffer {int dummy; } ;
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;
struct TYPE_3__ {struct vsp1_pipeline* pipe; } ;
struct TYPE_4__ {int /*<<< orphan*/  mem; TYPE_1__ entity; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 struct vsp1_vb2_buffer* to_vsp1_vb2_buffer (struct vb2_v4l2_buffer*) ; 
 struct vsp1_video* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_is_streaming (int /*<<< orphan*/ *) ; 
 scalar_t__ vsp1_pipeline_ready (struct vsp1_pipeline*) ; 
 int /*<<< orphan*/  vsp1_video_pipeline_run (struct vsp1_pipeline*) ; 

__attribute__((used)) static void vsp1_video_buffer_queue(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct vsp1_video *video = vb2_get_drv_priv(vb->vb2_queue);
	struct vsp1_pipeline *pipe = video->rwpf->entity.pipe;
	struct vsp1_vb2_buffer *buf = to_vsp1_vb2_buffer(vbuf);
	unsigned long flags;
	bool empty;

	spin_lock_irqsave(&video->irqlock, flags);
	empty = list_empty(&video->irqqueue);
	list_add_tail(&buf->queue, &video->irqqueue);
	spin_unlock_irqrestore(&video->irqlock, flags);

	if (!empty)
		return;

	spin_lock_irqsave(&pipe->irqlock, flags);

	video->rwpf->mem = buf->mem;
	pipe->buffers_ready |= 1 << video->pipe_index;

	if (vb2_is_streaming(&video->queue) &&
	    vsp1_pipeline_ready(pipe))
		vsp1_video_pipeline_run(pipe);

	spin_unlock_irqrestore(&pipe->irqlock, flags);
}