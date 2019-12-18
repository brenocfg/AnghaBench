#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  field; int /*<<< orphan*/  bytesperline; } ;
struct TYPE_11__ {TYPE_2__ pix; } ;
struct TYPE_12__ {TYPE_3__ fmt; } ;
struct isp_video_fh {int /*<<< orphan*/  queue; TYPE_4__ format; int /*<<< orphan*/  timeperframe; } ;
struct TYPE_14__ {int /*<<< orphan*/  pipe; } ;
struct TYPE_13__ {TYPE_6__ entity; } ;
struct isp_pipeline {int error; int state; int /*<<< orphan*/  ent_enum; int /*<<< orphan*/  field; int /*<<< orphan*/  frame_number; int /*<<< orphan*/  max_timeperframe; int /*<<< orphan*/  lock; int /*<<< orphan*/  pipe; int /*<<< orphan*/  l3_ick; int /*<<< orphan*/  max_rate; } ;
struct isp_video {int type; int bpl_padding; int /*<<< orphan*/  stream_lock; int /*<<< orphan*/ * queue; int /*<<< orphan*/  dmaqueue; TYPE_5__ video; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  bpl_value; TYPE_1__* isp; struct isp_pipeline pipe; } ;
struct file {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;
typedef  enum isp_pipeline_state { ____Placeholder_isp_pipeline_state } isp_pipeline_state ;
struct TYPE_9__ {int /*<<< orphan*/ * clock; int /*<<< orphan*/  media_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 size_t ISP_CLK_L3_ICK ; 
 int ISP_PIPELINE_IDLE_INPUT ; 
 int ISP_PIPELINE_IDLE_OUTPUT ; 
 int ISP_PIPELINE_STREAM ; 
 int ISP_PIPELINE_STREAM_INPUT ; 
 int ISP_PIPELINE_STREAM_OUTPUT ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int isp_video_check_external_subdevs (struct isp_video*,struct isp_pipeline*) ; 
 int isp_video_check_format (struct isp_video*,struct isp_video_fh*) ; 
 int isp_video_get_graph_data (struct isp_video*,struct isp_pipeline*) ; 
 int /*<<< orphan*/  media_entity_enum_cleanup (int /*<<< orphan*/ *) ; 
 int media_entity_enum_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int media_pipeline_start (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_pipeline_stop (TYPE_6__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct isp_pipeline* to_isp_pipeline (TYPE_6__*) ; 
 struct isp_video_fh* to_isp_video_fh (void*) ; 
 int vb2_streamon (int /*<<< orphan*/ *,int) ; 
 struct isp_video* video_drvdata (struct file*) ; 

__attribute__((used)) static int
isp_video_streamon(struct file *file, void *fh, enum v4l2_buf_type type)
{
	struct isp_video_fh *vfh = to_isp_video_fh(fh);
	struct isp_video *video = video_drvdata(file);
	enum isp_pipeline_state state;
	struct isp_pipeline *pipe;
	unsigned long flags;
	int ret;

	if (type != video->type)
		return -EINVAL;

	mutex_lock(&video->stream_lock);

	/* Start streaming on the pipeline. No link touching an entity in the
	 * pipeline can be activated or deactivated once streaming is started.
	 */
	pipe = video->video.entity.pipe
	     ? to_isp_pipeline(&video->video.entity) : &video->pipe;

	ret = media_entity_enum_init(&pipe->ent_enum, &video->isp->media_dev);
	if (ret)
		goto err_enum_init;

	/* TODO: Implement PM QoS */
	pipe->l3_ick = clk_get_rate(video->isp->clock[ISP_CLK_L3_ICK]);
	pipe->max_rate = pipe->l3_ick;

	ret = media_pipeline_start(&video->video.entity, &pipe->pipe);
	if (ret < 0)
		goto err_pipeline_start;

	/* Verify that the currently configured format matches the output of
	 * the connected subdev.
	 */
	ret = isp_video_check_format(video, vfh);
	if (ret < 0)
		goto err_check_format;

	video->bpl_padding = ret;
	video->bpl_value = vfh->format.fmt.pix.bytesperline;

	ret = isp_video_get_graph_data(video, pipe);
	if (ret < 0)
		goto err_check_format;

	if (video->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		state = ISP_PIPELINE_STREAM_OUTPUT | ISP_PIPELINE_IDLE_OUTPUT;
	else
		state = ISP_PIPELINE_STREAM_INPUT | ISP_PIPELINE_IDLE_INPUT;

	ret = isp_video_check_external_subdevs(video, pipe);
	if (ret < 0)
		goto err_check_format;

	pipe->error = false;

	spin_lock_irqsave(&pipe->lock, flags);
	pipe->state &= ~ISP_PIPELINE_STREAM;
	pipe->state |= state;
	spin_unlock_irqrestore(&pipe->lock, flags);

	/* Set the maximum time per frame as the value requested by userspace.
	 * This is a soft limit that can be overridden if the hardware doesn't
	 * support the request limit.
	 */
	if (video->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
		pipe->max_timeperframe = vfh->timeperframe;

	video->queue = &vfh->queue;
	INIT_LIST_HEAD(&video->dmaqueue);
	atomic_set(&pipe->frame_number, -1);
	pipe->field = vfh->format.fmt.pix.field;

	mutex_lock(&video->queue_lock);
	ret = vb2_streamon(&vfh->queue, type);
	mutex_unlock(&video->queue_lock);
	if (ret < 0)
		goto err_check_format;

	mutex_unlock(&video->stream_lock);

	return 0;

err_check_format:
	media_pipeline_stop(&video->video.entity);
err_pipeline_start:
	/* TODO: Implement PM QoS */
	/* The DMA queue must be emptied here, otherwise CCDC interrupts that
	 * will get triggered the next time the CCDC is powered up will try to
	 * access buffers that might have been freed but still present in the
	 * DMA queue. This can easily get triggered if the above
	 * omap3isp_pipeline_set_stream() call fails on a system with a
	 * free-running sensor.
	 */
	INIT_LIST_HEAD(&video->dmaqueue);
	video->queue = NULL;

	media_entity_enum_cleanup(&pipe->ent_enum);

err_enum_init:
	mutex_unlock(&video->stream_lock);

	return ret;
}