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
struct vsp1_pipeline {scalar_t__ state; int /*<<< orphan*/  irqlock; } ;

/* Variables and functions */
 scalar_t__ VSP1_PIPELINE_STOPPED ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

bool vsp1_pipeline_stopped(struct vsp1_pipeline *pipe)
{
	unsigned long flags;
	bool stopped;

	spin_lock_irqsave(&pipe->irqlock, flags);
	stopped = pipe->state == VSP1_PIPELINE_STOPPED;
	spin_unlock_irqrestore(&pipe->irqlock, flags);

	return stopped;
}