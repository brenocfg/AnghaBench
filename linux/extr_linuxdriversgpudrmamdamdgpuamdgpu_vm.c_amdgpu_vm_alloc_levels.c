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
typedef  unsigned int uint64_t ;
typedef  int /*<<< orphan*/  u64 ;
struct reservation_object {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  bo; } ;
struct amdgpu_vm_pt {TYPE_5__ base; struct reservation_object* resv; int /*<<< orphan*/  type; int /*<<< orphan*/  flags; int /*<<< orphan*/  domain; int /*<<< orphan*/  byte_align; int /*<<< orphan*/  size; struct amdgpu_vm_pt* entries; } ;
struct TYPE_8__ {TYPE_2__* bo; } ;
struct TYPE_9__ {TYPE_3__ base; } ;
struct amdgpu_vm {scalar_t__ use_cpu_for_update; TYPE_4__ root; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_bo_param {TYPE_5__ base; struct reservation_object* resv; int /*<<< orphan*/  type; int /*<<< orphan*/  flags; int /*<<< orphan*/  domain; int /*<<< orphan*/  byte_align; int /*<<< orphan*/  size; struct amdgpu_bo_param* entries; } ;
struct amdgpu_bo {int /*<<< orphan*/  parent; struct amdgpu_bo* shadow; } ;
typedef  int /*<<< orphan*/  bp ;
struct TYPE_6__ {struct reservation_object* resv; } ;
struct TYPE_7__ {TYPE_1__ tbo; scalar_t__ shadow; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED ; 
 int /*<<< orphan*/  AMDGPU_GEM_CREATE_NO_CPU_ACCESS ; 
 int /*<<< orphan*/  AMDGPU_GEM_CREATE_SHADOW ; 
 int /*<<< orphan*/  AMDGPU_GEM_CREATE_VRAM_CONTIGUOUS ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 int /*<<< orphan*/  AMDGPU_GPU_PAGE_SIZE ; 
 unsigned int AMDGPU_VM_PTB ; 
 int EINVAL ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int __GFP_ZERO ; 
 int amdgpu_bo_create (struct amdgpu_device*,struct amdgpu_vm_pt*,struct amdgpu_bo**) ; 
 int amdgpu_bo_kmap (struct amdgpu_bo*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_bo_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_bo_unref (struct amdgpu_bo**) ; 
 int /*<<< orphan*/  amdgpu_vm_bo_base_init (TYPE_5__*,struct amdgpu_vm*,struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_vm_bo_size (struct amdgpu_device*,unsigned int) ; 
 int amdgpu_vm_clear_bo (struct amdgpu_device*,struct amdgpu_vm*,struct amdgpu_bo*,unsigned int,int) ; 
 unsigned int amdgpu_vm_level_shift (struct amdgpu_device*,unsigned int) ; 
 unsigned int amdgpu_vm_num_entries (struct amdgpu_device*,unsigned int) ; 
 struct amdgpu_vm_pt* kvmalloc_array (unsigned int,int,int) ; 
 int /*<<< orphan*/  memset (struct amdgpu_vm_pt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ttm_bo_type_kernel ; 

__attribute__((used)) static int amdgpu_vm_alloc_levels(struct amdgpu_device *adev,
				  struct amdgpu_vm *vm,
				  struct amdgpu_vm_pt *parent,
				  uint64_t saddr, uint64_t eaddr,
				  unsigned level, bool ats)
{
	unsigned shift = amdgpu_vm_level_shift(adev, level);
	unsigned pt_idx, from, to;
	u64 flags;
	int r;

	if (!parent->entries) {
		unsigned num_entries = amdgpu_vm_num_entries(adev, level);

		parent->entries = kvmalloc_array(num_entries,
						   sizeof(struct amdgpu_vm_pt),
						   GFP_KERNEL | __GFP_ZERO);
		if (!parent->entries)
			return -ENOMEM;
		memset(parent->entries, 0 , sizeof(struct amdgpu_vm_pt));
	}

	from = saddr >> shift;
	to = eaddr >> shift;
	if (from >= amdgpu_vm_num_entries(adev, level) ||
	    to >= amdgpu_vm_num_entries(adev, level))
		return -EINVAL;

	++level;
	saddr = saddr & ((1 << shift) - 1);
	eaddr = eaddr & ((1 << shift) - 1);

	flags = AMDGPU_GEM_CREATE_VRAM_CONTIGUOUS;
	if (vm->root.base.bo->shadow)
		flags |= AMDGPU_GEM_CREATE_SHADOW;
	if (vm->use_cpu_for_update)
		flags |= AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED;
	else
		flags |= AMDGPU_GEM_CREATE_NO_CPU_ACCESS;

	/* walk over the address space and allocate the page tables */
	for (pt_idx = from; pt_idx <= to; ++pt_idx) {
		struct reservation_object *resv = vm->root.base.bo->tbo.resv;
		struct amdgpu_vm_pt *entry = &parent->entries[pt_idx];
		struct amdgpu_bo *pt;

		if (!entry->base.bo) {
			struct amdgpu_bo_param bp;

			memset(&bp, 0, sizeof(bp));
			bp.size = amdgpu_vm_bo_size(adev, level);
			bp.byte_align = AMDGPU_GPU_PAGE_SIZE;
			bp.domain = AMDGPU_GEM_DOMAIN_VRAM;
			bp.flags = flags;
			bp.type = ttm_bo_type_kernel;
			bp.resv = resv;
			r = amdgpu_bo_create(adev, &bp, &pt);
			if (r)
				return r;

			r = amdgpu_vm_clear_bo(adev, vm, pt, level, ats);
			if (r) {
				amdgpu_bo_unref(&pt->shadow);
				amdgpu_bo_unref(&pt);
				return r;
			}

			if (vm->use_cpu_for_update) {
				r = amdgpu_bo_kmap(pt, NULL);
				if (r) {
					amdgpu_bo_unref(&pt->shadow);
					amdgpu_bo_unref(&pt);
					return r;
				}
			}

			/* Keep a reference to the root directory to avoid
			* freeing them up in the wrong order.
			*/
			pt->parent = amdgpu_bo_ref(parent->base.bo);

			amdgpu_vm_bo_base_init(&entry->base, vm, pt);
		}

		if (level < AMDGPU_VM_PTB) {
			uint64_t sub_saddr = (pt_idx == from) ? saddr : 0;
			uint64_t sub_eaddr = (pt_idx == to) ? eaddr :
				((1 << shift) - 1);
			r = amdgpu_vm_alloc_levels(adev, vm, entry, sub_saddr,
						   sub_eaddr, level, ats);
			if (r)
				return r;
		}
	}

	return 0;
}