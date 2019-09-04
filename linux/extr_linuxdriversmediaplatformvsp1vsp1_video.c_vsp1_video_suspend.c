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
struct TYPE_4__ {int /*<<< orphan*/  index; struct vsp1_pipeline* pipe; } ;
struct vsp1_rwpf {TYPE_2__ entity; } ;
struct vsp1_pipeline {scalar_t__ state; int /*<<< orphan*/  wq; int /*<<< orphan*/  irqlock; } ;
struct vsp1_device {int /*<<< orphan*/  dev; struct vsp1_rwpf** wpf; TYPE_1__* info; } ;
struct TYPE_3__ {unsigned int wpf_count; } ;

/* Variables and functions */
 scalar_t__ VSP1_PIPELINE_RUNNING ; 
 scalar_t__ VSP1_PIPELINE_STOPPING ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vsp1_pipeline_stopped (struct vsp1_pipeline*) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vsp1_video_suspend(struct vsp1_device *vsp1)
{
	unsigned long flags;
	unsigned int i;
	int ret;

	/*
	 * To avoid increasing the system suspend time needlessly, loop over the
	 * pipelines twice, first to set them all to the stopping state, and
	 * then to wait for the stop to complete.
	 */
	for (i = 0; i < vsp1->info->wpf_count; ++i) {
		struct vsp1_rwpf *wpf = vsp1->wpf[i];
		struct vsp1_pipeline *pipe;

		if (wpf == NULL)
			continue;

		pipe = wpf->entity.pipe;
		if (pipe == NULL)
			continue;

		spin_lock_irqsave(&pipe->irqlock, flags);
		if (pipe->state == VSP1_PIPELINE_RUNNING)
			pipe->state = VSP1_PIPELINE_STOPPING;
		spin_unlock_irqrestore(&pipe->irqlock, flags);
	}

	for (i = 0; i < vsp1->info->wpf_count; ++i) {
		struct vsp1_rwpf *wpf = vsp1->wpf[i];
		struct vsp1_pipeline *pipe;

		if (wpf == NULL)
			continue;

		pipe = wpf->entity.pipe;
		if (pipe == NULL)
			continue;

		ret = wait_event_timeout(pipe->wq, vsp1_pipeline_stopped(pipe),
					 msecs_to_jiffies(500));
		if (ret == 0)
			dev_warn(vsp1->dev, "pipeline %u stop timeout\n",
				 wpf->entity.index);
	}
}