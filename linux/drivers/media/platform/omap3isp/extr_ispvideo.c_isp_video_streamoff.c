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
struct isp_video_fh {int /*<<< orphan*/  queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  entity; } ;
struct isp_video {int type; int error; int /*<<< orphan*/  stream_lock; TYPE_1__ video; int /*<<< orphan*/ * queue; int /*<<< orphan*/  queue_lock; } ;
struct isp_pipeline {int state; int /*<<< orphan*/  ent_enum; int /*<<< orphan*/  lock; } ;
struct file {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;
typedef  enum isp_pipeline_state { ____Placeholder_isp_pipeline_state } isp_pipeline_state ;

/* Variables and functions */
 int EINVAL ; 
 int ISP_PIPELINE_QUEUE_INPUT ; 
 int ISP_PIPELINE_QUEUE_OUTPUT ; 
 int ISP_PIPELINE_STREAM_INPUT ; 
 int ISP_PIPELINE_STREAM_OUTPUT ; 
 int /*<<< orphan*/  ISP_PIPELINE_STREAM_STOPPED ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  media_entity_enum_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_pipeline_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap3isp_pipeline_set_stream (struct isp_pipeline*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap3isp_video_cancel_stream (struct isp_video*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct isp_pipeline* to_isp_pipeline (int /*<<< orphan*/ *) ; 
 struct isp_video_fh* to_isp_video_fh (void*) ; 
 unsigned int vb2_is_streaming (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vb2_streamoff (int /*<<< orphan*/ *,int) ; 
 struct isp_video* video_drvdata (struct file*) ; 

__attribute__((used)) static int
isp_video_streamoff(struct file *file, void *fh, enum v4l2_buf_type type)
{
	struct isp_video_fh *vfh = to_isp_video_fh(fh);
	struct isp_video *video = video_drvdata(file);
	struct isp_pipeline *pipe = to_isp_pipeline(&video->video.entity);
	enum isp_pipeline_state state;
	unsigned int streaming;
	unsigned long flags;

	if (type != video->type)
		return -EINVAL;

	mutex_lock(&video->stream_lock);

	/* Make sure we're not streaming yet. */
	mutex_lock(&video->queue_lock);
	streaming = vb2_is_streaming(&vfh->queue);
	mutex_unlock(&video->queue_lock);

	if (!streaming)
		goto done;

	/* Update the pipeline state. */
	if (video->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		state = ISP_PIPELINE_STREAM_OUTPUT
		      | ISP_PIPELINE_QUEUE_OUTPUT;
	else
		state = ISP_PIPELINE_STREAM_INPUT
		      | ISP_PIPELINE_QUEUE_INPUT;

	spin_lock_irqsave(&pipe->lock, flags);
	pipe->state &= ~state;
	spin_unlock_irqrestore(&pipe->lock, flags);

	/* Stop the stream. */
	omap3isp_pipeline_set_stream(pipe, ISP_PIPELINE_STREAM_STOPPED);
	omap3isp_video_cancel_stream(video);

	mutex_lock(&video->queue_lock);
	vb2_streamoff(&vfh->queue, type);
	mutex_unlock(&video->queue_lock);
	video->queue = NULL;
	video->error = false;

	/* TODO: Implement PM QoS */
	media_pipeline_stop(&video->video.entity);

	media_entity_enum_cleanup(&pipe->ent_enum);

done:
	mutex_unlock(&video->stream_lock);
	return 0;
}