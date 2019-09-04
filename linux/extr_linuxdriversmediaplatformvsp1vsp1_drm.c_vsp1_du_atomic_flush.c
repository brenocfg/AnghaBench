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
struct vsp1_pipeline {int dummy; } ;
struct vsp1_du_atomic_pipe_config {int /*<<< orphan*/  crc; } ;
struct vsp1_drm_pipeline {int /*<<< orphan*/  crc; struct vsp1_pipeline pipe; } ;
struct vsp1_device {TYPE_1__* drm; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; struct vsp1_drm_pipeline* pipe; } ;

/* Variables and functions */
 struct vsp1_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vsp1_du_pipeline_configure (struct vsp1_pipeline*) ; 
 int /*<<< orphan*/  vsp1_du_pipeline_setup_inputs (struct vsp1_device*,struct vsp1_pipeline*) ; 

void vsp1_du_atomic_flush(struct device *dev, unsigned int pipe_index,
			  const struct vsp1_du_atomic_pipe_config *cfg)
{
	struct vsp1_device *vsp1 = dev_get_drvdata(dev);
	struct vsp1_drm_pipeline *drm_pipe = &vsp1->drm->pipe[pipe_index];
	struct vsp1_pipeline *pipe = &drm_pipe->pipe;

	drm_pipe->crc = cfg->crc;

	mutex_lock(&vsp1->drm->lock);
	vsp1_du_pipeline_setup_inputs(vsp1, pipe);
	vsp1_du_pipeline_configure(pipe);
	mutex_unlock(&vsp1->drm->lock);
}