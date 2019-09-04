#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_amdgpu_cs_chunk_ib {int va_start; int ib_bytes; } ;
struct TYPE_12__ {TYPE_7__* bo; } ;
struct TYPE_13__ {TYPE_5__ base; } ;
struct amdgpu_vm {TYPE_6__ root; } ;
struct amdgpu_ring {TYPE_2__* funcs; } ;
struct amdgpu_ib {int /*<<< orphan*/ * ptr; } ;
struct amdgpu_fpriv {struct amdgpu_vm vm; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_cs_parser {unsigned int nchunks; TYPE_3__* job; struct amdgpu_ring* ring; struct amdgpu_cs_chunk* chunks; TYPE_1__* filp; } ;
struct amdgpu_cs_chunk {scalar_t__ chunk_id; struct drm_amdgpu_cs_chunk_ib* kdata; } ;
struct amdgpu_bo_va_mapping {int last; int start; } ;
struct amdgpu_bo {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  resv; } ;
struct TYPE_14__ {TYPE_4__ tbo; } ;
struct TYPE_10__ {unsigned int num_ibs; int /*<<< orphan*/  vm_pd_addr; scalar_t__ vm; struct amdgpu_ib* ibs; } ;
struct TYPE_9__ {scalar_t__ parse_cs; scalar_t__ patch_cs_in_place; } ;
struct TYPE_8__ {struct amdgpu_fpriv* driver_priv; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_CHUNK_ID_IB ; 
 int AMDGPU_GPU_PAGE_SIZE ; 
 int AMDGPU_VA_HOLE_MASK ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  amdgpu_bo_gpu_offset (TYPE_7__*) ; 
 int amdgpu_bo_kmap (struct amdgpu_bo*,void**) ; 
 int /*<<< orphan*/  amdgpu_bo_kunmap (struct amdgpu_bo*) ; 
 int amdgpu_bo_vm_update_pte (struct amdgpu_cs_parser*) ; 
 int amdgpu_cs_find_mapping (struct amdgpu_cs_parser*,int,struct amdgpu_bo**,struct amdgpu_bo_va_mapping**) ; 
 int amdgpu_cs_sync_rings (struct amdgpu_cs_parser*) ; 
 int amdgpu_ring_parse_cs (struct amdgpu_ring*,struct amdgpu_cs_parser*,unsigned int) ; 
 int amdgpu_ring_patch_cs_in_place (struct amdgpu_ring*,struct amdgpu_cs_parser*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int reservation_object_reserve_shared (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amdgpu_cs_ib_vm_chunk(struct amdgpu_device *adev,
				 struct amdgpu_cs_parser *p)
{
	struct amdgpu_fpriv *fpriv = p->filp->driver_priv;
	struct amdgpu_vm *vm = &fpriv->vm;
	struct amdgpu_ring *ring = p->ring;
	int r;

	/* Only for UVD/VCE VM emulation */
	if (p->ring->funcs->parse_cs || p->ring->funcs->patch_cs_in_place) {
		unsigned i, j;

		for (i = 0, j = 0; i < p->nchunks && j < p->job->num_ibs; i++) {
			struct drm_amdgpu_cs_chunk_ib *chunk_ib;
			struct amdgpu_bo_va_mapping *m;
			struct amdgpu_bo *aobj = NULL;
			struct amdgpu_cs_chunk *chunk;
			uint64_t offset, va_start;
			struct amdgpu_ib *ib;
			uint8_t *kptr;

			chunk = &p->chunks[i];
			ib = &p->job->ibs[j];
			chunk_ib = chunk->kdata;

			if (chunk->chunk_id != AMDGPU_CHUNK_ID_IB)
				continue;

			va_start = chunk_ib->va_start & AMDGPU_VA_HOLE_MASK;
			r = amdgpu_cs_find_mapping(p, va_start, &aobj, &m);
			if (r) {
				DRM_ERROR("IB va_start is invalid\n");
				return r;
			}

			if ((va_start + chunk_ib->ib_bytes) >
			    (m->last + 1) * AMDGPU_GPU_PAGE_SIZE) {
				DRM_ERROR("IB va_start+ib_bytes is invalid\n");
				return -EINVAL;
			}

			/* the IB should be reserved at this point */
			r = amdgpu_bo_kmap(aobj, (void **)&kptr);
			if (r) {
				return r;
			}

			offset = m->start * AMDGPU_GPU_PAGE_SIZE;
			kptr += va_start - offset;

			if (p->ring->funcs->parse_cs) {
				memcpy(ib->ptr, kptr, chunk_ib->ib_bytes);
				amdgpu_bo_kunmap(aobj);

				r = amdgpu_ring_parse_cs(ring, p, j);
				if (r)
					return r;
			} else {
				ib->ptr = (uint32_t *)kptr;
				r = amdgpu_ring_patch_cs_in_place(ring, p, j);
				amdgpu_bo_kunmap(aobj);
				if (r)
					return r;
			}

			j++;
		}
	}

	if (p->job->vm) {
		p->job->vm_pd_addr = amdgpu_bo_gpu_offset(vm->root.base.bo);

		r = amdgpu_bo_vm_update_pte(p);
		if (r)
			return r;

		r = reservation_object_reserve_shared(vm->root.base.bo->tbo.resv);
		if (r)
			return r;
	}

	return amdgpu_cs_sync_rings(p);
}