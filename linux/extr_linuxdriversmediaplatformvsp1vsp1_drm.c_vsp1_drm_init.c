#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  list_pipe; } ;
struct vsp1_rwpf {TYPE_7__ entity; } ;
struct vsp1_pipeline {int /*<<< orphan*/  entities; TYPE_4__* lif; TYPE_3__* output; int /*<<< orphan*/  frame_end; } ;
struct vsp1_drm_pipeline {int /*<<< orphan*/ * uif; int /*<<< orphan*/  wait_queue; struct vsp1_pipeline pipe; } ;
struct vsp1_device {struct vsp1_rwpf** rpf; TYPE_6__* info; TYPE_5__** uif; TYPE_1__** lif; TYPE_3__** wpf; TYPE_8__* drm; int /*<<< orphan*/  dev; } ;
struct TYPE_16__ {struct vsp1_drm_pipeline* pipe; int /*<<< orphan*/  lock; } ;
struct TYPE_14__ {unsigned int lif_count; unsigned int uif_count; unsigned int rpf_count; } ;
struct TYPE_13__ {int /*<<< orphan*/  entity; } ;
struct TYPE_12__ {int /*<<< orphan*/  list_pipe; struct vsp1_pipeline* pipe; } ;
struct TYPE_10__ {int /*<<< orphan*/  list_pipe; scalar_t__ sink_pad; TYPE_4__* sink; struct vsp1_pipeline* pipe; } ;
struct TYPE_11__ {TYPE_2__ entity; } ;
struct TYPE_9__ {TYPE_4__ entity; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_8__* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vsp1_du_pipeline_frame_end ; 
 int /*<<< orphan*/  vsp1_pipeline_init (struct vsp1_pipeline*) ; 

int vsp1_drm_init(struct vsp1_device *vsp1)
{
	unsigned int i;

	vsp1->drm = devm_kzalloc(vsp1->dev, sizeof(*vsp1->drm), GFP_KERNEL);
	if (!vsp1->drm)
		return -ENOMEM;

	mutex_init(&vsp1->drm->lock);

	/* Create one DRM pipeline per LIF. */
	for (i = 0; i < vsp1->info->lif_count; ++i) {
		struct vsp1_drm_pipeline *drm_pipe = &vsp1->drm->pipe[i];
		struct vsp1_pipeline *pipe = &drm_pipe->pipe;

		init_waitqueue_head(&drm_pipe->wait_queue);

		vsp1_pipeline_init(pipe);

		pipe->frame_end = vsp1_du_pipeline_frame_end;

		/*
		 * The output side of the DRM pipeline is static, add the
		 * corresponding entities manually.
		 */
		pipe->output = vsp1->wpf[i];
		pipe->lif = &vsp1->lif[i]->entity;

		pipe->output->entity.pipe = pipe;
		pipe->output->entity.sink = pipe->lif;
		pipe->output->entity.sink_pad = 0;
		list_add_tail(&pipe->output->entity.list_pipe, &pipe->entities);

		pipe->lif->pipe = pipe;
		list_add_tail(&pipe->lif->list_pipe, &pipe->entities);

		/*
		 * CRC computation is initially disabled, don't add the UIF to
		 * the pipeline.
		 */
		if (i < vsp1->info->uif_count)
			drm_pipe->uif = &vsp1->uif[i]->entity;
	}

	/* Disable all RPFs initially. */
	for (i = 0; i < vsp1->info->rpf_count; ++i) {
		struct vsp1_rwpf *input = vsp1->rpf[i];

		INIT_LIST_HEAD(&input->entity.list_pipe);
	}

	return 0;
}