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
struct vsp1_pipeline {int /*<<< orphan*/  kref; } ;
struct TYPE_3__ {struct vsp1_pipeline* pipe; } ;
struct TYPE_4__ {TYPE_1__ entity; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct vsp1_pipeline* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct vsp1_pipeline*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 struct vsp1_pipeline* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsp1_pipeline_reset (struct vsp1_pipeline*) ; 
 int vsp1_video_pipeline_init (struct vsp1_pipeline*,struct vsp1_video*) ; 

__attribute__((used)) static struct vsp1_pipeline *vsp1_video_pipeline_get(struct vsp1_video *video)
{
	struct vsp1_pipeline *pipe;
	int ret;

	/*
	 * Get a pipeline object for the video node. If a pipeline has already
	 * been allocated just increment its reference count and return it.
	 * Otherwise allocate a new pipeline and initialize it, it will be freed
	 * when the last reference is released.
	 */
	if (!video->rwpf->entity.pipe) {
		pipe = kzalloc(sizeof(*pipe), GFP_KERNEL);
		if (!pipe)
			return ERR_PTR(-ENOMEM);

		ret = vsp1_video_pipeline_init(pipe, video);
		if (ret < 0) {
			vsp1_pipeline_reset(pipe);
			kfree(pipe);
			return ERR_PTR(ret);
		}
	} else {
		pipe = video->rwpf->entity.pipe;
		kref_get(&pipe->kref);
	}

	return pipe;
}