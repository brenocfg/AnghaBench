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
struct vb2_queue {int dummy; } ;
struct isp_video_fh {struct isp_video* video; } ;
struct TYPE_2__ {int /*<<< orphan*/  entity; } ;
struct isp_video {int /*<<< orphan*/  irqlock; int /*<<< orphan*/  dmaqueue_flags; int /*<<< orphan*/  dmaqueue; TYPE_1__ video; } ;
struct isp_pipeline {scalar_t__ input; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_PIPELINE_STREAM_CONTINUOUS ; 
 int /*<<< orphan*/  ISP_VIDEO_DMAQUEUE_UNDERRUN ; 
 int /*<<< orphan*/  VB2_BUF_STATE_QUEUED ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int omap3isp_pipeline_set_stream (struct isp_pipeline*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap3isp_video_return_buffers (struct isp_video*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct isp_pipeline* to_isp_pipeline (int /*<<< orphan*/ *) ; 
 struct isp_video_fh* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int isp_video_start_streaming(struct vb2_queue *queue,
				     unsigned int count)
{
	struct isp_video_fh *vfh = vb2_get_drv_priv(queue);
	struct isp_video *video = vfh->video;
	struct isp_pipeline *pipe = to_isp_pipeline(&video->video.entity);
	unsigned long flags;
	int ret;

	/* In sensor-to-memory mode, the stream can be started synchronously
	 * to the stream on command. In memory-to-memory mode, it will be
	 * started when buffers are queued on both the input and output.
	 */
	if (pipe->input)
		return 0;

	ret = omap3isp_pipeline_set_stream(pipe,
					   ISP_PIPELINE_STREAM_CONTINUOUS);
	if (ret < 0) {
		spin_lock_irqsave(&video->irqlock, flags);
		omap3isp_video_return_buffers(video, VB2_BUF_STATE_QUEUED);
		spin_unlock_irqrestore(&video->irqlock, flags);
		return ret;
	}

	spin_lock_irqsave(&video->irqlock, flags);
	if (list_empty(&video->dmaqueue))
		video->dmaqueue_flags |= ISP_VIDEO_DMAQUEUE_UNDERRUN;
	spin_unlock_irqrestore(&video->irqlock, flags);

	return 0;
}