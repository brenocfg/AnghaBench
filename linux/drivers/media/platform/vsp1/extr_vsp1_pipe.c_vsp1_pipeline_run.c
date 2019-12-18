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
struct vsp1_pipeline {scalar_t__ state; scalar_t__ buffers_ready; TYPE_2__* output; } ;
struct vsp1_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  index; struct vsp1_device* vsp1; } ;
struct TYPE_4__ {TYPE_1__ entity; } ;

/* Variables and functions */
 int /*<<< orphan*/  VI6_CMD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VI6_CMD_STRCMD ; 
 scalar_t__ VSP1_PIPELINE_RUNNING ; 
 scalar_t__ VSP1_PIPELINE_STOPPED ; 
 int /*<<< orphan*/  vsp1_write (struct vsp1_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vsp1_pipeline_run(struct vsp1_pipeline *pipe)
{
	struct vsp1_device *vsp1 = pipe->output->entity.vsp1;

	if (pipe->state == VSP1_PIPELINE_STOPPED) {
		vsp1_write(vsp1, VI6_CMD(pipe->output->entity.index),
			   VI6_CMD_STRCMD);
		pipe->state = VSP1_PIPELINE_RUNNING;
	}

	pipe->buffers_ready = 0;
}