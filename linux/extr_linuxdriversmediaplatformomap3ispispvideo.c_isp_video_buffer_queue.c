#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vb2_v4l2_buffer {int dummy; } ;
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;
struct isp_video_fh {struct isp_video* video; } ;
struct TYPE_4__ {int /*<<< orphan*/  entity; } ;
struct isp_video {scalar_t__ type; int /*<<< orphan*/  dmaqueue_flags; TYPE_3__* ops; int /*<<< orphan*/  irqlock; int /*<<< orphan*/  dmaqueue; int /*<<< orphan*/  error; TYPE_1__ video; } ;
struct isp_pipeline {int state; int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  vb2_buf; } ;
struct isp_buffer {int /*<<< orphan*/  irqlist; TYPE_2__ vb; } ;
typedef  enum isp_pipeline_state { ____Placeholder_isp_pipeline_state } isp_pipeline_state ;
struct TYPE_6__ {int /*<<< orphan*/  (* queue ) (struct isp_video*,struct isp_buffer*) ;} ;

/* Variables and functions */
 int ISP_PIPELINE_QUEUE_INPUT ; 
 int ISP_PIPELINE_QUEUE_OUTPUT ; 
 int ISP_PIPELINE_STREAM ; 
 int /*<<< orphan*/  ISP_PIPELINE_STREAM_SINGLESHOT ; 
 int /*<<< orphan*/  ISP_VIDEO_DMAQUEUE_QUEUED ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 unsigned int isp_pipeline_ready (struct isp_pipeline*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap3isp_pipeline_set_stream (struct isp_pipeline*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct isp_video*,struct isp_buffer*) ; 
 struct isp_buffer* to_isp_buffer (struct vb2_v4l2_buffer*) ; 
 struct isp_pipeline* to_isp_pipeline (int /*<<< orphan*/ *) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_buffer_done (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct isp_video_fh* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isp_video_buffer_queue(struct vb2_buffer *buf)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(buf);
	struct isp_video_fh *vfh = vb2_get_drv_priv(buf->vb2_queue);
	struct isp_buffer *buffer = to_isp_buffer(vbuf);
	struct isp_video *video = vfh->video;
	struct isp_pipeline *pipe = to_isp_pipeline(&video->video.entity);
	enum isp_pipeline_state state;
	unsigned long flags;
	unsigned int empty;
	unsigned int start;

	spin_lock_irqsave(&video->irqlock, flags);

	if (unlikely(video->error)) {
		vb2_buffer_done(&buffer->vb.vb2_buf, VB2_BUF_STATE_ERROR);
		spin_unlock_irqrestore(&video->irqlock, flags);
		return;
	}

	empty = list_empty(&video->dmaqueue);
	list_add_tail(&buffer->irqlist, &video->dmaqueue);

	spin_unlock_irqrestore(&video->irqlock, flags);

	if (empty) {
		if (video->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
			state = ISP_PIPELINE_QUEUE_OUTPUT;
		else
			state = ISP_PIPELINE_QUEUE_INPUT;

		spin_lock_irqsave(&pipe->lock, flags);
		pipe->state |= state;
		video->ops->queue(video, buffer);
		video->dmaqueue_flags |= ISP_VIDEO_DMAQUEUE_QUEUED;

		start = isp_pipeline_ready(pipe);
		if (start)
			pipe->state |= ISP_PIPELINE_STREAM;
		spin_unlock_irqrestore(&pipe->lock, flags);

		if (start)
			omap3isp_pipeline_set_stream(pipe,
						ISP_PIPELINE_STREAM_SINGLESHOT);
	}
}