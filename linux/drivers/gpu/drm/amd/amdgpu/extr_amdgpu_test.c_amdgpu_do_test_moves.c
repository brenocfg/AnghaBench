#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct dma_fence {int dummy; } ;
struct amdgpu_ring {int dummy; } ;
struct TYPE_12__ {unsigned int gart_size; int gart_start; int vram_start; } ;
struct TYPE_10__ {scalar_t__ ring_size; scalar_t__ ring_obj; } ;
struct TYPE_11__ {TYPE_4__ ih; } ;
struct TYPE_9__ {scalar_t__ wb_obj; } ;
struct TYPE_7__ {struct amdgpu_ring* buffer_funcs_ring; } ;
struct amdgpu_device {TYPE_6__ gmc; TYPE_5__ irq; TYPE_3__ wb; TYPE_2__** rings; TYPE_1__ mman; } ;
struct amdgpu_bo_param {unsigned int size; void* domain; int /*<<< orphan*/ * resv; int /*<<< orphan*/  type; scalar_t__ flags; int /*<<< orphan*/  byte_align; } ;
struct amdgpu_bo {int /*<<< orphan*/  tbo; } ;
typedef  int /*<<< orphan*/  bp ;
struct TYPE_8__ {scalar_t__ ring_size; } ;

/* Variables and functions */
 void* AMDGPU_GEM_DOMAIN_GTT ; 
 void* AMDGPU_GEM_DOMAIN_VRAM ; 
 scalar_t__ AMDGPU_GPU_PAGE_SIZE ; 
 int AMDGPU_IB_POOL_SIZE ; 
 int AMDGPU_MAX_RINGS ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int amdgpu_bo_create (struct amdgpu_device*,struct amdgpu_bo_param*,struct amdgpu_bo**) ; 
 int amdgpu_bo_gpu_offset (struct amdgpu_bo*) ; 
 int amdgpu_bo_kmap (struct amdgpu_bo*,void**) ; 
 int /*<<< orphan*/  amdgpu_bo_kunmap (struct amdgpu_bo*) ; 
 int amdgpu_bo_pin (struct amdgpu_bo*,void*) ; 
 int amdgpu_bo_reserve (struct amdgpu_bo*,int) ; 
 int /*<<< orphan*/  amdgpu_bo_unpin (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_bo_unref (struct amdgpu_bo**) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (struct amdgpu_bo*) ; 
 int amdgpu_copy_buffer (struct amdgpu_ring*,int,int,unsigned int,int /*<<< orphan*/ *,struct dma_fence**,int,int) ; 
 int amdgpu_ttm_alloc_gart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int dma_fence_wait (struct dma_fence*,int) ; 
 struct amdgpu_bo** kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct amdgpu_bo**) ; 
 int /*<<< orphan*/  memset (struct amdgpu_bo_param*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  ttm_bo_type_kernel ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void amdgpu_do_test_moves(struct amdgpu_device *adev)
{
	struct amdgpu_ring *ring = adev->mman.buffer_funcs_ring;
	struct amdgpu_bo *vram_obj = NULL;
	struct amdgpu_bo **gtt_obj = NULL;
	struct amdgpu_bo_param bp;
	uint64_t gart_addr, vram_addr;
	unsigned n, size;
	int i, r;

	size = 1024 * 1024;

	/* Number of tests =
	 * (Total GTT - IB pool - writeback page - ring buffers) / test size
	 */
	n = adev->gmc.gart_size - AMDGPU_IB_POOL_SIZE*64*1024;
	for (i = 0; i < AMDGPU_MAX_RINGS; ++i)
		if (adev->rings[i])
			n -= adev->rings[i]->ring_size;
	if (adev->wb.wb_obj)
		n -= AMDGPU_GPU_PAGE_SIZE;
	if (adev->irq.ih.ring_obj)
		n -= adev->irq.ih.ring_size;
	n /= size;

	gtt_obj = kcalloc(n, sizeof(*gtt_obj), GFP_KERNEL);
	if (!gtt_obj) {
		DRM_ERROR("Failed to allocate %d pointers\n", n);
		r = 1;
		goto out_cleanup;
	}
	memset(&bp, 0, sizeof(bp));
	bp.size = size;
	bp.byte_align = PAGE_SIZE;
	bp.domain = AMDGPU_GEM_DOMAIN_VRAM;
	bp.flags = 0;
	bp.type = ttm_bo_type_kernel;
	bp.resv = NULL;

	r = amdgpu_bo_create(adev, &bp, &vram_obj);
	if (r) {
		DRM_ERROR("Failed to create VRAM object\n");
		goto out_cleanup;
	}
	r = amdgpu_bo_reserve(vram_obj, false);
	if (unlikely(r != 0))
		goto out_unref;
	r = amdgpu_bo_pin(vram_obj, AMDGPU_GEM_DOMAIN_VRAM);
	if (r) {
		DRM_ERROR("Failed to pin VRAM object\n");
		goto out_unres;
	}
	vram_addr = amdgpu_bo_gpu_offset(vram_obj);
	for (i = 0; i < n; i++) {
		void *gtt_map, *vram_map;
		void **gart_start, **gart_end;
		void **vram_start, **vram_end;
		struct dma_fence *fence = NULL;

		bp.domain = AMDGPU_GEM_DOMAIN_GTT;
		r = amdgpu_bo_create(adev, &bp, gtt_obj + i);
		if (r) {
			DRM_ERROR("Failed to create GTT object %d\n", i);
			goto out_lclean;
		}

		r = amdgpu_bo_reserve(gtt_obj[i], false);
		if (unlikely(r != 0))
			goto out_lclean_unref;
		r = amdgpu_bo_pin(gtt_obj[i], AMDGPU_GEM_DOMAIN_GTT);
		if (r) {
			DRM_ERROR("Failed to pin GTT object %d\n", i);
			goto out_lclean_unres;
		}
		r = amdgpu_ttm_alloc_gart(&gtt_obj[i]->tbo);
		if (r) {
			DRM_ERROR("%p bind failed\n", gtt_obj[i]);
			goto out_lclean_unpin;
		}
		gart_addr = amdgpu_bo_gpu_offset(gtt_obj[i]);

		r = amdgpu_bo_kmap(gtt_obj[i], &gtt_map);
		if (r) {
			DRM_ERROR("Failed to map GTT object %d\n", i);
			goto out_lclean_unpin;
		}

		for (gart_start = gtt_map, gart_end = gtt_map + size;
		     gart_start < gart_end;
		     gart_start++)
			*gart_start = gart_start;

		amdgpu_bo_kunmap(gtt_obj[i]);

		r = amdgpu_copy_buffer(ring, gart_addr, vram_addr,
				       size, NULL, &fence, false, false);

		if (r) {
			DRM_ERROR("Failed GTT->VRAM copy %d\n", i);
			goto out_lclean_unpin;
		}

		r = dma_fence_wait(fence, false);
		if (r) {
			DRM_ERROR("Failed to wait for GTT->VRAM fence %d\n", i);
			goto out_lclean_unpin;
		}

		dma_fence_put(fence);

		r = amdgpu_bo_kmap(vram_obj, &vram_map);
		if (r) {
			DRM_ERROR("Failed to map VRAM object after copy %d\n", i);
			goto out_lclean_unpin;
		}

		for (gart_start = gtt_map, gart_end = gtt_map + size,
		     vram_start = vram_map, vram_end = vram_map + size;
		     vram_start < vram_end;
		     gart_start++, vram_start++) {
			if (*vram_start != gart_start) {
				DRM_ERROR("Incorrect GTT->VRAM copy %d: Got 0x%p, "
					  "expected 0x%p (GTT/VRAM offset "
					  "0x%16llx/0x%16llx)\n",
					  i, *vram_start, gart_start,
					  (unsigned long long)
					  (gart_addr - adev->gmc.gart_start +
					   (void*)gart_start - gtt_map),
					  (unsigned long long)
					  (vram_addr - adev->gmc.vram_start +
					   (void*)gart_start - gtt_map));
				amdgpu_bo_kunmap(vram_obj);
				goto out_lclean_unpin;
			}
			*vram_start = vram_start;
		}

		amdgpu_bo_kunmap(vram_obj);

		r = amdgpu_copy_buffer(ring, vram_addr, gart_addr,
				       size, NULL, &fence, false, false);

		if (r) {
			DRM_ERROR("Failed VRAM->GTT copy %d\n", i);
			goto out_lclean_unpin;
		}

		r = dma_fence_wait(fence, false);
		if (r) {
			DRM_ERROR("Failed to wait for VRAM->GTT fence %d\n", i);
			goto out_lclean_unpin;
		}

		dma_fence_put(fence);

		r = amdgpu_bo_kmap(gtt_obj[i], &gtt_map);
		if (r) {
			DRM_ERROR("Failed to map GTT object after copy %d\n", i);
			goto out_lclean_unpin;
		}

		for (gart_start = gtt_map, gart_end = gtt_map + size,
		     vram_start = vram_map, vram_end = vram_map + size;
		     gart_start < gart_end;
		     gart_start++, vram_start++) {
			if (*gart_start != vram_start) {
				DRM_ERROR("Incorrect VRAM->GTT copy %d: Got 0x%p, "
					  "expected 0x%p (VRAM/GTT offset "
					  "0x%16llx/0x%16llx)\n",
					  i, *gart_start, vram_start,
					  (unsigned long long)
					  (vram_addr - adev->gmc.vram_start +
					   (void*)vram_start - vram_map),
					  (unsigned long long)
					  (gart_addr - adev->gmc.gart_start +
					   (void*)vram_start - vram_map));
				amdgpu_bo_kunmap(gtt_obj[i]);
				goto out_lclean_unpin;
			}
		}

		amdgpu_bo_kunmap(gtt_obj[i]);

		DRM_INFO("Tested GTT->VRAM and VRAM->GTT copy for GTT offset 0x%llx\n",
			 gart_addr - adev->gmc.gart_start);
		continue;

out_lclean_unpin:
		amdgpu_bo_unpin(gtt_obj[i]);
out_lclean_unres:
		amdgpu_bo_unreserve(gtt_obj[i]);
out_lclean_unref:
		amdgpu_bo_unref(&gtt_obj[i]);
out_lclean:
		for (--i; i >= 0; --i) {
			amdgpu_bo_unpin(gtt_obj[i]);
			amdgpu_bo_unreserve(gtt_obj[i]);
			amdgpu_bo_unref(&gtt_obj[i]);
		}
		if (fence)
			dma_fence_put(fence);
		break;
	}

	amdgpu_bo_unpin(vram_obj);
out_unres:
	amdgpu_bo_unreserve(vram_obj);
out_unref:
	amdgpu_bo_unref(&vram_obj);
out_cleanup:
	kfree(gtt_obj);
	if (r) {
		pr_warn("Error while testing BO move\n");
	}
}