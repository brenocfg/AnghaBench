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
struct vsp1_pipeline {TYPE_3__* output; } ;
struct vsp1_du_writeback_config {int /*<<< orphan*/ * mem; int /*<<< orphan*/  pitch; scalar_t__ pixelformat; } ;
struct vsp1_du_atomic_pipe_config {struct vsp1_du_writeback_config writeback; int /*<<< orphan*/  crc; } ;
struct vsp1_drm_pipeline {int /*<<< orphan*/  crc; struct vsp1_pipeline pipe; } ;
struct vsp1_device {TYPE_2__* drm; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_6__ {int writeback; TYPE_1__ mem; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; struct vsp1_drm_pipeline* pipe; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 struct vsp1_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vsp1_du_pipeline_configure (struct vsp1_pipeline*) ; 
 int vsp1_du_pipeline_set_rwpf_format (struct vsp1_device*,TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsp1_du_pipeline_setup_inputs (struct vsp1_device*,struct vsp1_pipeline*) ; 

void vsp1_du_atomic_flush(struct device *dev, unsigned int pipe_index,
			  const struct vsp1_du_atomic_pipe_config *cfg)
{
	struct vsp1_device *vsp1 = dev_get_drvdata(dev);
	struct vsp1_drm_pipeline *drm_pipe = &vsp1->drm->pipe[pipe_index];
	struct vsp1_pipeline *pipe = &drm_pipe->pipe;
	int ret;

	drm_pipe->crc = cfg->crc;

	mutex_lock(&vsp1->drm->lock);

	if (cfg->writeback.pixelformat) {
		const struct vsp1_du_writeback_config *wb_cfg = &cfg->writeback;

		ret = vsp1_du_pipeline_set_rwpf_format(vsp1, pipe->output,
						       wb_cfg->pixelformat,
						       wb_cfg->pitch);
		if (WARN_ON(ret < 0))
			goto done;

		pipe->output->mem.addr[0] = wb_cfg->mem[0];
		pipe->output->mem.addr[1] = wb_cfg->mem[1];
		pipe->output->mem.addr[2] = wb_cfg->mem[2];
		pipe->output->writeback = true;
	}

	vsp1_du_pipeline_setup_inputs(vsp1, pipe);
	vsp1_du_pipeline_configure(pipe);

done:
	mutex_unlock(&vsp1->drm->lock);
}