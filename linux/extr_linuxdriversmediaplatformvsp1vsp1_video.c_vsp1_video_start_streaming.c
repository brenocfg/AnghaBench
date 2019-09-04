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
struct vsp1_video {TYPE_2__* rwpf; } ;
struct vsp1_pipeline {scalar_t__ stream_count; scalar_t__ num_inputs; int /*<<< orphan*/  irqlock; int /*<<< orphan*/  lock; } ;
struct vb2_queue {int dummy; } ;
struct TYPE_3__ {struct vsp1_pipeline* pipe; } ;
struct TYPE_4__ {TYPE_1__ entity; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vsp1_video* vb2_get_drv_priv (struct vb2_queue*) ; 
 scalar_t__ vsp1_pipeline_ready (struct vsp1_pipeline*) ; 
 int /*<<< orphan*/  vsp1_video_cleanup_pipeline (struct vsp1_pipeline*) ; 
 int /*<<< orphan*/  vsp1_video_pipeline_run (struct vsp1_pipeline*) ; 
 int /*<<< orphan*/  vsp1_video_release_buffers (struct vsp1_video*) ; 
 int vsp1_video_setup_pipeline (struct vsp1_pipeline*) ; 

__attribute__((used)) static int vsp1_video_start_streaming(struct vb2_queue *vq, unsigned int count)
{
	struct vsp1_video *video = vb2_get_drv_priv(vq);
	struct vsp1_pipeline *pipe = video->rwpf->entity.pipe;
	bool start_pipeline = false;
	unsigned long flags;
	int ret;

	mutex_lock(&pipe->lock);
	if (pipe->stream_count == pipe->num_inputs) {
		ret = vsp1_video_setup_pipeline(pipe);
		if (ret < 0) {
			vsp1_video_release_buffers(video);
			vsp1_video_cleanup_pipeline(pipe);
			mutex_unlock(&pipe->lock);
			return ret;
		}

		start_pipeline = true;
	}

	pipe->stream_count++;
	mutex_unlock(&pipe->lock);

	/*
	 * vsp1_pipeline_ready() is not sufficient to establish that all streams
	 * are prepared and the pipeline is configured, as multiple streams
	 * can race through streamon with buffers already queued; Therefore we
	 * don't even attempt to start the pipeline until the last stream has
	 * called through here.
	 */
	if (!start_pipeline)
		return 0;

	spin_lock_irqsave(&pipe->irqlock, flags);
	if (vsp1_pipeline_ready(pipe))
		vsp1_video_pipeline_run(pipe);
	spin_unlock_irqrestore(&pipe->irqlock, flags);

	return 0;
}