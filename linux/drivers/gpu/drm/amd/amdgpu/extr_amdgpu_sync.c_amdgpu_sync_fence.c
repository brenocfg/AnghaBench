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
struct dma_fence {int /*<<< orphan*/  context; } ;
struct amdgpu_sync_entry {int explicit; int /*<<< orphan*/  fence; int /*<<< orphan*/  node; } ;
struct amdgpu_sync {int /*<<< orphan*/  fences; int /*<<< orphan*/  last_vm_update; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FENCE_OWNER_VM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ amdgpu_sync_add_later (struct amdgpu_sync*,struct dma_fence*,int) ; 
 scalar_t__ amdgpu_sync_get_owner (struct dma_fence*) ; 
 int /*<<< orphan*/  amdgpu_sync_keep_later (int /*<<< orphan*/ *,struct dma_fence*) ; 
 scalar_t__ amdgpu_sync_same_dev (struct amdgpu_device*,struct dma_fence*) ; 
 int /*<<< orphan*/  amdgpu_sync_slab ; 
 int /*<<< orphan*/  dma_fence_get (struct dma_fence*) ; 
 int /*<<< orphan*/  hash_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct amdgpu_sync_entry* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int amdgpu_sync_fence(struct amdgpu_device *adev, struct amdgpu_sync *sync,
		      struct dma_fence *f, bool explicit)
{
	struct amdgpu_sync_entry *e;

	if (!f)
		return 0;
	if (amdgpu_sync_same_dev(adev, f) &&
	    amdgpu_sync_get_owner(f) == AMDGPU_FENCE_OWNER_VM)
		amdgpu_sync_keep_later(&sync->last_vm_update, f);

	if (amdgpu_sync_add_later(sync, f, explicit))
		return 0;

	e = kmem_cache_alloc(amdgpu_sync_slab, GFP_KERNEL);
	if (!e)
		return -ENOMEM;

	e->explicit = explicit;

	hash_add(sync->fences, &e->node, f->context);
	e->fence = dma_fence_get(f);
	return 0;
}