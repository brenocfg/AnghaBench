#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct drm_sched_rq {int dummy; } ;
struct drm_file {int dummy; } ;
struct dma_fence {int dummy; } ;
struct TYPE_5__ {struct drm_sched_rq* sched_rq; } ;
struct amdgpu_ring {TYPE_1__ sched; } ;
struct TYPE_6__ {struct amdgpu_ring ring; } ;
struct TYPE_7__ {TYPE_2__ kiq; } ;
struct amdgpu_device {unsigned int num_rings; TYPE_3__ gfx; struct amdgpu_ring** rings; int /*<<< orphan*/  vram_lost_counter; int /*<<< orphan*/  gpu_reset_counter; } ;
struct amdgpu_ctx {int init_priority; int /*<<< orphan*/ * fences; TYPE_4__* rings; int /*<<< orphan*/  queue_mgr; int /*<<< orphan*/  guilty; int /*<<< orphan*/  override_priority; void* vram_lost_counter; void* reset_counter; void* reset_counter_query; int /*<<< orphan*/  lock; int /*<<< orphan*/  ring_lock; int /*<<< orphan*/  refcount; struct amdgpu_device* adev; } ;
typedef  enum drm_sched_priority { ____Placeholder_drm_sched_priority } drm_sched_priority ;
struct TYPE_8__ {int sequence; int /*<<< orphan*/  entity; int /*<<< orphan*/ * fences; } ;

/* Variables and functions */
 unsigned int AMDGPU_MAX_RINGS ; 
 int DRM_SCHED_PRIORITY_MAX ; 
 int /*<<< orphan*/  DRM_SCHED_PRIORITY_UNSET ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int amdgpu_ctx_priority_permit (struct drm_file*,int) ; 
 int amdgpu_queue_mgr_init (struct amdgpu_device*,int /*<<< orphan*/ *) ; 
 unsigned int amdgpu_sched_jobs ; 
 void* atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_sched_entity_destroy (int /*<<< orphan*/ *) ; 
 int drm_sched_entity_init (int /*<<< orphan*/ *,struct drm_sched_rq**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct amdgpu_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amdgpu_ctx_init(struct amdgpu_device *adev,
			   enum drm_sched_priority priority,
			   struct drm_file *filp,
			   struct amdgpu_ctx *ctx)
{
	unsigned i, j;
	int r;

	if (priority < 0 || priority >= DRM_SCHED_PRIORITY_MAX)
		return -EINVAL;

	r = amdgpu_ctx_priority_permit(filp, priority);
	if (r)
		return r;

	memset(ctx, 0, sizeof(*ctx));
	ctx->adev = adev;
	kref_init(&ctx->refcount);
	spin_lock_init(&ctx->ring_lock);
	ctx->fences = kcalloc(amdgpu_sched_jobs * AMDGPU_MAX_RINGS,
			      sizeof(struct dma_fence*), GFP_KERNEL);
	if (!ctx->fences)
		return -ENOMEM;

	mutex_init(&ctx->lock);

	for (i = 0; i < AMDGPU_MAX_RINGS; ++i) {
		ctx->rings[i].sequence = 1;
		ctx->rings[i].fences = &ctx->fences[amdgpu_sched_jobs * i];
	}

	ctx->reset_counter = atomic_read(&adev->gpu_reset_counter);
	ctx->reset_counter_query = ctx->reset_counter;
	ctx->vram_lost_counter = atomic_read(&adev->vram_lost_counter);
	ctx->init_priority = priority;
	ctx->override_priority = DRM_SCHED_PRIORITY_UNSET;

	/* create context entity for each ring */
	for (i = 0; i < adev->num_rings; i++) {
		struct amdgpu_ring *ring = adev->rings[i];
		struct drm_sched_rq *rq;

		rq = &ring->sched.sched_rq[priority];

		if (ring == &adev->gfx.kiq.ring)
			continue;

		r = drm_sched_entity_init(&ctx->rings[i].entity,
					  &rq, 1, &ctx->guilty);
		if (r)
			goto failed;
	}

	r = amdgpu_queue_mgr_init(adev, &ctx->queue_mgr);
	if (r)
		goto failed;

	return 0;

failed:
	for (j = 0; j < i; j++)
		drm_sched_entity_destroy(&ctx->rings[j].entity);
	kfree(ctx->fences);
	ctx->fences = NULL;
	return r;
}