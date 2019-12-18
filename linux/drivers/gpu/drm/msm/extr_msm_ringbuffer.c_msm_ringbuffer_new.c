#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct msm_ringbuffer {int id; int /*<<< orphan*/  fctx; int /*<<< orphan*/  lock; int /*<<< orphan*/  submits; int /*<<< orphan*/  memptrs_iova; void* memptrs; scalar_t__ start; scalar_t__ cur; scalar_t__ next; scalar_t__ end; int /*<<< orphan*/  bo; int /*<<< orphan*/  iova; struct msm_gpu* gpu; } ;
struct msm_gpu {int /*<<< orphan*/  dev; int /*<<< orphan*/  aspace; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENOMEM ; 
 struct msm_ringbuffer* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int /*<<< orphan*/  MSM_BO_WC ; 
 int MSM_GPU_RINGBUFFER_SZ ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 struct msm_ringbuffer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_fence_context_alloc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ msm_gem_kernel_new (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_gem_object_set_name (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msm_ringbuffer_destroy (struct msm_ringbuffer*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct msm_ringbuffer *msm_ringbuffer_new(struct msm_gpu *gpu, int id,
		void *memptrs, uint64_t memptrs_iova)
{
	struct msm_ringbuffer *ring;
	char name[32];
	int ret;

	/* We assume everwhere that MSM_GPU_RINGBUFFER_SZ is a power of 2 */
	BUILD_BUG_ON(!is_power_of_2(MSM_GPU_RINGBUFFER_SZ));

	ring = kzalloc(sizeof(*ring), GFP_KERNEL);
	if (!ring) {
		ret = -ENOMEM;
		goto fail;
	}

	ring->gpu = gpu;
	ring->id = id;

	ring->start = msm_gem_kernel_new(gpu->dev, MSM_GPU_RINGBUFFER_SZ,
		MSM_BO_WC, gpu->aspace, &ring->bo, &ring->iova);

	if (IS_ERR(ring->start)) {
		ret = PTR_ERR(ring->start);
		ring->start = 0;
		goto fail;
	}

	msm_gem_object_set_name(ring->bo, "ring%d", id);

	ring->end   = ring->start + (MSM_GPU_RINGBUFFER_SZ >> 2);
	ring->next  = ring->start;
	ring->cur   = ring->start;

	ring->memptrs = memptrs;
	ring->memptrs_iova = memptrs_iova;

	INIT_LIST_HEAD(&ring->submits);
	spin_lock_init(&ring->lock);

	snprintf(name, sizeof(name), "gpu-ring-%d", ring->id);

	ring->fctx = msm_fence_context_alloc(gpu->dev, name);

	return ring;

fail:
	msm_ringbuffer_destroy(ring);
	return ERR_PTR(ret);
}