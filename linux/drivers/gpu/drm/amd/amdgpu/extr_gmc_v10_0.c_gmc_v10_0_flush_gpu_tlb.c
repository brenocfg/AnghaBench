#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct dma_fence {int dummy; } ;
struct amdgpu_ring {TYPE_3__* funcs; } ;
struct amdgpu_job {int vm_needs_flush; TYPE_5__* ibs; int /*<<< orphan*/  vm_pd_addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  gtt_window_lock; int /*<<< orphan*/  entity; int /*<<< orphan*/  buffer_funcs_enabled; struct amdgpu_ring* buffer_funcs_ring; } ;
struct TYPE_7__ {int /*<<< orphan*/  bo; } ;
struct amdgpu_device {TYPE_4__ mman; TYPE_2__ gart; scalar_t__ in_gpu_reset; int /*<<< orphan*/  ib_pool_ready; TYPE_1__* nbio_funcs; } ;
struct TYPE_10__ {int /*<<< orphan*/  length_dw; int /*<<< orphan*/ * ptr; } ;
struct TYPE_8__ {int /*<<< orphan*/  nop; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* hdp_flush ) (struct amdgpu_device*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_FENCE_OWNER_UNDEFINED ; 
 scalar_t__ AMDGPU_GFXHUB_0 ; 
 scalar_t__ AMDGPU_MMHUB_0 ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  amdgpu_gmc_pd_addr (int /*<<< orphan*/ ) ; 
 int amdgpu_job_alloc_with_ib (struct amdgpu_device*,int,struct amdgpu_job**) ; 
 int /*<<< orphan*/  amdgpu_job_free (struct amdgpu_job*) ; 
 int amdgpu_job_submit (struct amdgpu_job*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dma_fence**) ; 
 int /*<<< orphan*/  amdgpu_ring_pad_ib (struct amdgpu_ring*,TYPE_5__*) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_wait (struct dma_fence*,int) ; 
 int /*<<< orphan*/  gmc_v10_0_flush_vm_hub (struct amdgpu_device*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gmc_v10_0_flush_gpu_tlb(struct amdgpu_device *adev, uint32_t vmid,
					uint32_t vmhub, uint32_t flush_type)
{
	struct amdgpu_ring *ring = adev->mman.buffer_funcs_ring;
	struct dma_fence *fence;
	struct amdgpu_job *job;

	int r;

	/* flush hdp cache */
	adev->nbio_funcs->hdp_flush(adev, NULL);

	mutex_lock(&adev->mman.gtt_window_lock);

	if (vmhub == AMDGPU_MMHUB_0) {
		gmc_v10_0_flush_vm_hub(adev, vmid, AMDGPU_MMHUB_0, 0);
		mutex_unlock(&adev->mman.gtt_window_lock);
		return;
	}

	BUG_ON(vmhub != AMDGPU_GFXHUB_0);

	if (!adev->mman.buffer_funcs_enabled ||
	    !adev->ib_pool_ready ||
	    adev->in_gpu_reset) {
		gmc_v10_0_flush_vm_hub(adev, vmid, AMDGPU_GFXHUB_0, 0);
		mutex_unlock(&adev->mman.gtt_window_lock);
		return;
	}

	/* The SDMA on Navi has a bug which can theoretically result in memory
	 * corruption if an invalidation happens at the same time as an VA
	 * translation. Avoid this by doing the invalidation from the SDMA
	 * itself.
	 */
	r = amdgpu_job_alloc_with_ib(adev, 16 * 4, &job);
	if (r)
		goto error_alloc;

	job->vm_pd_addr = amdgpu_gmc_pd_addr(adev->gart.bo);
	job->vm_needs_flush = true;
	job->ibs->ptr[job->ibs->length_dw++] = ring->funcs->nop;
	amdgpu_ring_pad_ib(ring, &job->ibs[0]);
	r = amdgpu_job_submit(job, &adev->mman.entity,
			      AMDGPU_FENCE_OWNER_UNDEFINED, &fence);
	if (r)
		goto error_submit;

	mutex_unlock(&adev->mman.gtt_window_lock);

	dma_fence_wait(fence, false);
	dma_fence_put(fence);

	return;

error_submit:
	amdgpu_job_free(job);

error_alloc:
	mutex_unlock(&adev->mman.gtt_window_lock);
	DRM_ERROR("Error flushing GPU TLB using the SDMA (%d)!\n", r);
}