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
struct vsp1_pipeline {int state; int /*<<< orphan*/  irqlock; int /*<<< orphan*/  wq; TYPE_3__* output; TYPE_3__** inputs; } ;
struct vsp1_device {TYPE_2__* info; } ;
typedef  enum vsp1_pipeline_state { ____Placeholder_vsp1_pipeline_state } vsp1_pipeline_state ;
struct TYPE_4__ {struct vsp1_device* vsp1; } ;
struct TYPE_6__ {TYPE_1__ entity; } ;
struct TYPE_5__ {unsigned int rpf_count; } ;

/* Variables and functions */
 unsigned int VSP1_DL_FRAME_END_COMPLETED ; 
 int VSP1_PIPELINE_STOPPED ; 
 int VSP1_PIPELINE_STOPPING ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ vsp1_pipeline_ready (struct vsp1_pipeline*) ; 
 int /*<<< orphan*/  vsp1_video_frame_end (struct vsp1_pipeline*,TYPE_3__*) ; 
 int /*<<< orphan*/  vsp1_video_pipeline_run (struct vsp1_pipeline*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vsp1_video_pipeline_frame_end(struct vsp1_pipeline *pipe,
					  unsigned int completion)
{
	struct vsp1_device *vsp1 = pipe->output->entity.vsp1;
	enum vsp1_pipeline_state state;
	unsigned long flags;
	unsigned int i;

	/* M2M Pipelines should never call here with an incomplete frame. */
	WARN_ON_ONCE(!(completion & VSP1_DL_FRAME_END_COMPLETED));

	spin_lock_irqsave(&pipe->irqlock, flags);

	/* Complete buffers on all video nodes. */
	for (i = 0; i < vsp1->info->rpf_count; ++i) {
		if (!pipe->inputs[i])
			continue;

		vsp1_video_frame_end(pipe, pipe->inputs[i]);
	}

	vsp1_video_frame_end(pipe, pipe->output);

	state = pipe->state;
	pipe->state = VSP1_PIPELINE_STOPPED;

	/*
	 * If a stop has been requested, mark the pipeline as stopped and
	 * return. Otherwise restart the pipeline if ready.
	 */
	if (state == VSP1_PIPELINE_STOPPING)
		wake_up(&pipe->wq);
	else if (vsp1_pipeline_ready(pipe))
		vsp1_video_pipeline_run(pipe);

	spin_unlock_irqrestore(&pipe->irqlock, flags);
}