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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct nvkm_vmm_page {scalar_t__ shift; struct nvkm_vmm_desc* desc; } ;
struct nvkm_vmm_func {struct nvkm_vmm_page* page; } ;
struct nvkm_vmm_desc {int bits; int size; int /*<<< orphan*/  align; } ;
struct nvkm_vmm {char const* name; scalar_t__ start; unsigned long long limit; int /*<<< orphan*/  list; void* root; void* free; TYPE_2__* pd; int /*<<< orphan*/  join; int /*<<< orphan*/  mutex; int /*<<< orphan*/  kref; int /*<<< orphan*/  debug; struct nvkm_mmu* mmu; struct nvkm_vmm_func const* func; } ;
struct nvkm_vma {int /*<<< orphan*/  head; } ;
struct TYPE_3__ {int /*<<< orphan*/  debug; } ;
struct nvkm_mmu {TYPE_1__ subdev; } ;
struct lock_class_key {int dummy; } ;
struct TYPE_4__ {int* refs; int /*<<< orphan*/ * pt; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NVKM_VMM_LEVELS_MAX ; 
 void* RB_ROOT ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __mutex_init (int /*<<< orphan*/ *,char*,struct lock_class_key*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_mmu_ptc_get (struct nvkm_mmu*,scalar_t__ const,int /*<<< orphan*/ ,int) ; 
 struct nvkm_vma* nvkm_vma_new (scalar_t__,scalar_t__) ; 
 int nvkm_vmm_ctor_managed (struct nvkm_vmm*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  nvkm_vmm_free_insert (struct nvkm_vmm*,struct nvkm_vma*) ; 
 TYPE_2__* nvkm_vmm_pt_new (struct nvkm_vmm_desc const*,int,int /*<<< orphan*/ *) ; 

int
nvkm_vmm_ctor(const struct nvkm_vmm_func *func, struct nvkm_mmu *mmu,
	      u32 pd_header, bool managed, u64 addr, u64 size,
	      struct lock_class_key *key, const char *name,
	      struct nvkm_vmm *vmm)
{
	static struct lock_class_key _key;
	const struct nvkm_vmm_page *page = func->page;
	const struct nvkm_vmm_desc *desc;
	struct nvkm_vma *vma;
	int levels, bits = 0, ret;

	vmm->func = func;
	vmm->mmu = mmu;
	vmm->name = name;
	vmm->debug = mmu->subdev.debug;
	kref_init(&vmm->kref);

	__mutex_init(&vmm->mutex, "&vmm->mutex", key ? key : &_key);

	/* Locate the smallest page size supported by the backend, it will
	 * have the the deepest nesting of page tables.
	 */
	while (page[1].shift)
		page++;

	/* Locate the structure that describes the layout of the top-level
	 * page table, and determine the number of valid bits in a virtual
	 * address.
	 */
	for (levels = 0, desc = page->desc; desc->bits; desc++, levels++)
		bits += desc->bits;
	bits += page->shift;
	desc--;

	if (WARN_ON(levels > NVKM_VMM_LEVELS_MAX))
		return -EINVAL;

	/* Allocate top-level page table. */
	vmm->pd = nvkm_vmm_pt_new(desc, false, NULL);
	if (!vmm->pd)
		return -ENOMEM;
	vmm->pd->refs[0] = 1;
	INIT_LIST_HEAD(&vmm->join);

	/* ... and the GPU storage for it, except on Tesla-class GPUs that
	 * have the PD embedded in the instance structure.
	 */
	if (desc->size) {
		const u32 size = pd_header + desc->size * (1 << desc->bits);
		vmm->pd->pt[0] = nvkm_mmu_ptc_get(mmu, size, desc->align, true);
		if (!vmm->pd->pt[0])
			return -ENOMEM;
	}

	/* Initialise address-space MM. */
	INIT_LIST_HEAD(&vmm->list);
	vmm->free = RB_ROOT;
	vmm->root = RB_ROOT;

	if (managed) {
		/* Address-space will be managed by the client for the most
		 * part, except for a specified area where NVKM allocations
		 * are allowed to be placed.
		 */
		vmm->start = 0;
		vmm->limit = 1ULL << bits;
		if (addr + size < addr || addr + size > vmm->limit)
			return -EINVAL;

		/* Client-managed area before the NVKM-managed area. */
		if (addr && (ret = nvkm_vmm_ctor_managed(vmm, 0, addr)))
			return ret;

		/* NVKM-managed area. */
		if (size) {
			if (!(vma = nvkm_vma_new(addr, size)))
				return -ENOMEM;
			nvkm_vmm_free_insert(vmm, vma);
			list_add_tail(&vma->head, &vmm->list);
		}

		/* Client-managed area after the NVKM-managed area. */
		addr = addr + size;
		size = vmm->limit - addr;
		if (size && (ret = nvkm_vmm_ctor_managed(vmm, addr, size)))
			return ret;
	} else {
		/* Address-space fully managed by NVKM, requiring calls to
		 * nvkm_vmm_get()/nvkm_vmm_put() to allocate address-space.
		 */
		vmm->start = addr;
		vmm->limit = size ? (addr + size) : (1ULL << bits);
		if (vmm->start > vmm->limit || vmm->limit > (1ULL << bits))
			return -EINVAL;

		if (!(vma = nvkm_vma_new(vmm->start, vmm->limit - vmm->start)))
			return -ENOMEM;

		nvkm_vmm_free_insert(vmm, vma);
		list_add(&vma->head, &vmm->list);
	}

	return 0;
}