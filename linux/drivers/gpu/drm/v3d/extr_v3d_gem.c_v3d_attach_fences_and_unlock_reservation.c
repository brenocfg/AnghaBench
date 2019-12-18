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
typedef  int /*<<< orphan*/  u32 ;
struct ww_acquire_ctx {int dummy; } ;
struct v3d_job {int bo_count; TYPE_1__** bo; int /*<<< orphan*/  done_fence; } ;
struct drm_syncobj {int dummy; } ;
struct drm_file {int dummy; } ;
struct dma_fence {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  resv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_resv_add_excl_fence (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_unlock_reservations (TYPE_1__**,int,struct ww_acquire_ctx*) ; 
 struct drm_syncobj* drm_syncobj_find (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_syncobj_put (struct drm_syncobj*) ; 
 int /*<<< orphan*/  drm_syncobj_replace_fence (struct drm_syncobj*,struct dma_fence*) ; 

__attribute__((used)) static void
v3d_attach_fences_and_unlock_reservation(struct drm_file *file_priv,
					 struct v3d_job *job,
					 struct ww_acquire_ctx *acquire_ctx,
					 u32 out_sync,
					 struct dma_fence *done_fence)
{
	struct drm_syncobj *sync_out;
	int i;

	for (i = 0; i < job->bo_count; i++) {
		/* XXX: Use shared fences for read-only objects. */
		dma_resv_add_excl_fence(job->bo[i]->resv,
						  job->done_fence);
	}

	drm_gem_unlock_reservations(job->bo, job->bo_count, acquire_ctx);

	/* Update the return sync object for the job */
	sync_out = drm_syncobj_find(file_priv, out_sync);
	if (sync_out) {
		drm_syncobj_replace_fence(sync_out, done_fence);
		drm_syncobj_put(sync_out);
	}
}