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
typedef  int /*<<< orphan*/  uint64_t ;
struct msm_ringbuffer {int /*<<< orphan*/  submits; scalar_t__ seqno; } ;
struct msm_gpu {TYPE_3__* funcs; TYPE_1__* pdev; struct drm_device* dev; } ;
struct msm_gem_submit {int nr_bos; int /*<<< orphan*/  fence; TYPE_2__* bos; int /*<<< orphan*/  aspace; int /*<<< orphan*/  node; scalar_t__ seqno; struct msm_ringbuffer* ring; } ;
struct msm_gem_object {int /*<<< orphan*/  base; struct msm_gpu* gpu; } ;
struct msm_file_private {int dummy; } ;
struct msm_drm_private {struct msm_file_private* lastctx; int /*<<< orphan*/  rd; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; struct msm_drm_private* dev_private; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* submit ) (struct msm_gpu*,struct msm_gem_submit*,struct msm_file_private*) ;} ;
struct TYPE_5__ {int flags; struct msm_gem_object* obj; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MSM_SUBMIT_BO_READ ; 
 int MSM_SUBMIT_BO_WRITE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  drm_gem_object_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hangcheck_timer_reset (struct msm_gpu*) ; 
 scalar_t__ is_active (struct msm_gem_object*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_gem_get_and_pin_iova (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_gem_move_to_active (int /*<<< orphan*/ *,struct msm_gpu*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_gpu_hw_init (struct msm_gpu*) ; 
 int /*<<< orphan*/  msm_rd_dump_submit (int /*<<< orphan*/ ,struct msm_gem_submit*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct msm_gpu*,struct msm_gem_submit*,struct msm_file_private*) ; 
 int /*<<< orphan*/  update_sw_cntrs (struct msm_gpu*) ; 

void msm_gpu_submit(struct msm_gpu *gpu, struct msm_gem_submit *submit,
		struct msm_file_private *ctx)
{
	struct drm_device *dev = gpu->dev;
	struct msm_drm_private *priv = dev->dev_private;
	struct msm_ringbuffer *ring = submit->ring;
	int i;

	WARN_ON(!mutex_is_locked(&dev->struct_mutex));

	pm_runtime_get_sync(&gpu->pdev->dev);

	msm_gpu_hw_init(gpu);

	submit->seqno = ++ring->seqno;

	list_add_tail(&submit->node, &ring->submits);

	msm_rd_dump_submit(priv->rd, submit, NULL);

	update_sw_cntrs(gpu);

	for (i = 0; i < submit->nr_bos; i++) {
		struct msm_gem_object *msm_obj = submit->bos[i].obj;
		uint64_t iova;

		/* can't happen yet.. but when we add 2d support we'll have
		 * to deal w/ cross-ring synchronization:
		 */
		WARN_ON(is_active(msm_obj) && (msm_obj->gpu != gpu));

		/* submit takes a reference to the bo and iova until retired: */
		drm_gem_object_get(&msm_obj->base);
		msm_gem_get_and_pin_iova(&msm_obj->base, submit->aspace, &iova);

		if (submit->bos[i].flags & MSM_SUBMIT_BO_WRITE)
			msm_gem_move_to_active(&msm_obj->base, gpu, true, submit->fence);
		else if (submit->bos[i].flags & MSM_SUBMIT_BO_READ)
			msm_gem_move_to_active(&msm_obj->base, gpu, false, submit->fence);
	}

	gpu->funcs->submit(gpu, submit, ctx);
	priv->lastctx = ctx;

	hangcheck_timer_reset(gpu);
}