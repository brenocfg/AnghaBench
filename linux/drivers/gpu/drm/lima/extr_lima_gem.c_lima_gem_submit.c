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
struct ww_acquire_ctx {int dummy; } ;
struct lima_vm {int dummy; } ;
struct lima_submit {int nr_bos; int flags; int /*<<< orphan*/  task; TYPE_2__* bos; scalar_t__ pipe; TYPE_1__* ctx; scalar_t__ out_sync; struct lima_bo** lbos; } ;
struct lima_drm_priv {struct lima_vm* vm; } ;
struct drm_gem_object {int /*<<< orphan*/  resv; } ;
struct lima_bo {struct drm_gem_object gem; } ;
struct drm_syncobj {int dummy; } ;
struct drm_file {int dummy; } ;
struct dma_fence {int dummy; } ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  handle; } ;
struct TYPE_3__ {scalar_t__ context; } ;

/* Variables and functions */
 int ENOENT ; 
 int LIMA_SUBMIT_BO_WRITE ; 
 int LIMA_SUBMIT_FLAG_EXPLICIT_FENCE ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_resv_add_excl_fence (int /*<<< orphan*/ ,struct dma_fence*) ; 
 int /*<<< orphan*/  dma_resv_add_shared_fence (int /*<<< orphan*/ ,struct dma_fence*) ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 struct drm_syncobj* drm_syncobj_find (struct drm_file*,scalar_t__) ; 
 int /*<<< orphan*/  drm_syncobj_put (struct drm_syncobj*) ; 
 int /*<<< orphan*/  drm_syncobj_replace_fence (struct drm_syncobj*,struct dma_fence*) ; 
 int lima_gem_add_deps (struct drm_file*,struct lima_submit*) ; 
 int lima_gem_lock_bos (struct lima_bo**,int,struct ww_acquire_ctx*) ; 
 int lima_gem_sync_bo (int /*<<< orphan*/ ,struct lima_bo*,int,int) ; 
 int /*<<< orphan*/  lima_gem_unlock_bos (struct lima_bo**,int,struct ww_acquire_ctx*) ; 
 struct dma_fence* lima_sched_context_queue_task (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lima_sched_task_fini (int /*<<< orphan*/ ) ; 
 int lima_sched_task_init (int /*<<< orphan*/ ,scalar_t__,struct lima_bo**,int,struct lima_vm*) ; 
 int lima_vm_bo_add (struct lima_vm*,struct lima_bo*,int) ; 
 int /*<<< orphan*/  lima_vm_bo_del (struct lima_vm*,struct lima_bo*) ; 
 struct lima_bo* to_lima_bo (struct drm_gem_object*) ; 
 struct lima_drm_priv* to_lima_drm_priv (struct drm_file*) ; 

int lima_gem_submit(struct drm_file *file, struct lima_submit *submit)
{
	int i, err = 0;
	struct ww_acquire_ctx ctx;
	struct lima_drm_priv *priv = to_lima_drm_priv(file);
	struct lima_vm *vm = priv->vm;
	struct drm_syncobj *out_sync = NULL;
	struct dma_fence *fence;
	struct lima_bo **bos = submit->lbos;

	if (submit->out_sync) {
		out_sync = drm_syncobj_find(file, submit->out_sync);
		if (!out_sync)
			return -ENOENT;
	}

	for (i = 0; i < submit->nr_bos; i++) {
		struct drm_gem_object *obj;
		struct lima_bo *bo;

		obj = drm_gem_object_lookup(file, submit->bos[i].handle);
		if (!obj) {
			err = -ENOENT;
			goto err_out0;
		}

		bo = to_lima_bo(obj);

		/* increase refcnt of gpu va map to prevent unmapped when executing,
		 * will be decreased when task done
		 */
		err = lima_vm_bo_add(vm, bo, false);
		if (err) {
			drm_gem_object_put_unlocked(obj);
			goto err_out0;
		}

		bos[i] = bo;
	}

	err = lima_gem_lock_bos(bos, submit->nr_bos, &ctx);
	if (err)
		goto err_out0;

	err = lima_sched_task_init(
		submit->task, submit->ctx->context + submit->pipe,
		bos, submit->nr_bos, vm);
	if (err)
		goto err_out1;

	err = lima_gem_add_deps(file, submit);
	if (err)
		goto err_out2;

	for (i = 0; i < submit->nr_bos; i++) {
		err = lima_gem_sync_bo(
			submit->task, bos[i],
			submit->bos[i].flags & LIMA_SUBMIT_BO_WRITE,
			submit->flags & LIMA_SUBMIT_FLAG_EXPLICIT_FENCE);
		if (err)
			goto err_out2;
	}

	fence = lima_sched_context_queue_task(
		submit->ctx->context + submit->pipe, submit->task);

	for (i = 0; i < submit->nr_bos; i++) {
		if (submit->bos[i].flags & LIMA_SUBMIT_BO_WRITE)
			dma_resv_add_excl_fence(bos[i]->gem.resv, fence);
		else
			dma_resv_add_shared_fence(bos[i]->gem.resv, fence);
	}

	lima_gem_unlock_bos(bos, submit->nr_bos, &ctx);

	for (i = 0; i < submit->nr_bos; i++)
		drm_gem_object_put_unlocked(&bos[i]->gem);

	if (out_sync) {
		drm_syncobj_replace_fence(out_sync, fence);
		drm_syncobj_put(out_sync);
	}

	dma_fence_put(fence);

	return 0;

err_out2:
	lima_sched_task_fini(submit->task);
err_out1:
	lima_gem_unlock_bos(bos, submit->nr_bos, &ctx);
err_out0:
	for (i = 0; i < submit->nr_bos; i++) {
		if (!bos[i])
			break;
		lima_vm_bo_del(vm, bos[i]);
		drm_gem_object_put_unlocked(&bos[i]->gem);
	}
	if (out_sync)
		drm_syncobj_put(out_sync);
	return err;
}