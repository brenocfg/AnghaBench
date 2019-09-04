#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ww_acquire_ctx {int dummy; } ;
struct v3d_file_priv {int /*<<< orphan*/ * sched_entity; } ;
struct TYPE_9__ {TYPE_2__* s_fence; } ;
struct TYPE_8__ {TYPE_4__ base; int /*<<< orphan*/  end; int /*<<< orphan*/  start; struct v3d_exec_info* exec; int /*<<< orphan*/  in_fence; } ;
struct TYPE_6__ {scalar_t__ start; scalar_t__ end; TYPE_4__ base; struct v3d_exec_info* exec; int /*<<< orphan*/  in_fence; } ;
struct v3d_exec_info {TYPE_3__ render; int /*<<< orphan*/  refcount; TYPE_1__ bin; int /*<<< orphan*/  bin_done_fence; int /*<<< orphan*/  unref_list; struct v3d_dev* v3d; int /*<<< orphan*/  qts; int /*<<< orphan*/  qms; int /*<<< orphan*/  qma; } ;
struct v3d_dev {int /*<<< orphan*/  sched_lock; int /*<<< orphan*/  dev; } ;
struct drm_v3d_submit_cl {scalar_t__ pad; scalar_t__ bcl_start; scalar_t__ bcl_end; int /*<<< orphan*/  out_sync; int /*<<< orphan*/  rcl_end; int /*<<< orphan*/  rcl_start; int /*<<< orphan*/  qts; int /*<<< orphan*/  qms; int /*<<< orphan*/  qma; int /*<<< orphan*/  in_sync_rcl; int /*<<< orphan*/  in_sync_bcl; } ;
struct drm_syncobj {int dummy; } ;
struct drm_file {struct v3d_file_priv* driver_priv; } ;
struct drm_device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  finished; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,scalar_t__) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 size_t V3D_BIN ; 
 size_t V3D_RENDER ; 
 int /*<<< orphan*/  dma_fence_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_sched_entity_push_job (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int drm_sched_job_init (TYPE_4__*,int /*<<< orphan*/ *,struct v3d_file_priv*) ; 
 struct drm_syncobj* drm_syncobj_find (struct drm_file*,int /*<<< orphan*/ ) ; 
 int drm_syncobj_find_fence (struct drm_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_syncobj_put (struct drm_syncobj*) ; 
 int /*<<< orphan*/  drm_syncobj_replace_fence (struct drm_syncobj*,int /*<<< orphan*/ *) ; 
 struct v3d_exec_info* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct v3d_exec_info*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 struct v3d_dev* to_v3d_dev (struct drm_device*) ; 
 int /*<<< orphan*/  v3d_attach_object_fences (struct v3d_exec_info*) ; 
 int v3d_cl_lookup_bos (struct drm_device*,struct drm_file*,struct drm_v3d_submit_cl*,struct v3d_exec_info*) ; 
 int /*<<< orphan*/  v3d_exec_put (struct v3d_exec_info*) ; 
 int v3d_lock_bo_reservations (struct drm_device*,struct v3d_exec_info*,struct ww_acquire_ctx*) ; 
 int /*<<< orphan*/  v3d_unlock_bo_reservations (struct drm_device*,struct v3d_exec_info*,struct ww_acquire_ctx*) ; 

int
v3d_submit_cl_ioctl(struct drm_device *dev, void *data,
		    struct drm_file *file_priv)
{
	struct v3d_dev *v3d = to_v3d_dev(dev);
	struct v3d_file_priv *v3d_priv = file_priv->driver_priv;
	struct drm_v3d_submit_cl *args = data;
	struct v3d_exec_info *exec;
	struct ww_acquire_ctx acquire_ctx;
	struct drm_syncobj *sync_out;
	int ret = 0;

	if (args->pad != 0) {
		DRM_INFO("pad must be zero: %d\n", args->pad);
		return -EINVAL;
	}

	exec = kcalloc(1, sizeof(*exec), GFP_KERNEL);
	if (!exec)
		return -ENOMEM;

	ret = pm_runtime_get_sync(v3d->dev);
	if (ret < 0) {
		kfree(exec);
		return ret;
	}

	kref_init(&exec->refcount);

	ret = drm_syncobj_find_fence(file_priv, args->in_sync_bcl,
				     &exec->bin.in_fence);
	if (ret == -EINVAL)
		goto fail;

	ret = drm_syncobj_find_fence(file_priv, args->in_sync_rcl,
				     &exec->render.in_fence);
	if (ret == -EINVAL)
		goto fail;

	exec->qma = args->qma;
	exec->qms = args->qms;
	exec->qts = args->qts;
	exec->bin.exec = exec;
	exec->bin.start = args->bcl_start;
	exec->bin.end = args->bcl_end;
	exec->render.exec = exec;
	exec->render.start = args->rcl_start;
	exec->render.end = args->rcl_end;
	exec->v3d = v3d;
	INIT_LIST_HEAD(&exec->unref_list);

	ret = v3d_cl_lookup_bos(dev, file_priv, args, exec);
	if (ret)
		goto fail;

	ret = v3d_lock_bo_reservations(dev, exec, &acquire_ctx);
	if (ret)
		goto fail;

	mutex_lock(&v3d->sched_lock);
	if (exec->bin.start != exec->bin.end) {
		ret = drm_sched_job_init(&exec->bin.base,
					 &v3d_priv->sched_entity[V3D_BIN],
					 v3d_priv);
		if (ret)
			goto fail_unreserve;

		exec->bin_done_fence =
			dma_fence_get(&exec->bin.base.s_fence->finished);

		kref_get(&exec->refcount); /* put by scheduler job completion */
		drm_sched_entity_push_job(&exec->bin.base,
					  &v3d_priv->sched_entity[V3D_BIN]);
	}

	ret = drm_sched_job_init(&exec->render.base,
				 &v3d_priv->sched_entity[V3D_RENDER],
				 v3d_priv);
	if (ret)
		goto fail_unreserve;

	kref_get(&exec->refcount); /* put by scheduler job completion */
	drm_sched_entity_push_job(&exec->render.base,
				  &v3d_priv->sched_entity[V3D_RENDER]);
	mutex_unlock(&v3d->sched_lock);

	v3d_attach_object_fences(exec);

	v3d_unlock_bo_reservations(dev, exec, &acquire_ctx);

	/* Update the return sync object for the */
	sync_out = drm_syncobj_find(file_priv, args->out_sync);
	if (sync_out) {
		drm_syncobj_replace_fence(sync_out,
					  &exec->render.base.s_fence->finished);
		drm_syncobj_put(sync_out);
	}

	v3d_exec_put(exec);

	return 0;

fail_unreserve:
	mutex_unlock(&v3d->sched_lock);
	v3d_unlock_bo_reservations(dev, exec, &acquire_ctx);
fail:
	v3d_exec_put(exec);

	return ret;
}