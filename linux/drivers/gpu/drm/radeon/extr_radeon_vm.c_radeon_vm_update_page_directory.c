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
typedef  scalar_t__ uint64_t ;
typedef  unsigned int uint32_t ;
struct radeon_vm {int max_pde_used; TYPE_1__* page_tables; struct radeon_bo* page_directory; } ;
struct radeon_ib {unsigned int length_dw; TYPE_4__* fence; int /*<<< orphan*/  sync; } ;
struct radeon_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  resv; } ;
struct TYPE_7__ {TYPE_2__ base; } ;
struct radeon_bo {TYPE_3__ tbo; } ;
struct TYPE_8__ {int is_vm_update; } ;
struct TYPE_5__ {scalar_t__ addr; struct radeon_bo* bo; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  R600_PTE_VALID ; 
 int /*<<< orphan*/  R600_RING_TYPE_DMA_INDEX ; 
 int RADEON_VM_PTE_COUNT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  radeon_asic_vm_pad_ib (struct radeon_device*,struct radeon_ib*) ; 
 int /*<<< orphan*/  radeon_bo_fence (struct radeon_bo*,TYPE_4__*,int) ; 
 scalar_t__ radeon_bo_gpu_offset (struct radeon_bo*) ; 
 int /*<<< orphan*/  radeon_ib_free (struct radeon_device*,struct radeon_ib*) ; 
 int radeon_ib_get (struct radeon_device*,int /*<<< orphan*/ ,struct radeon_ib*,int /*<<< orphan*/ *,unsigned int) ; 
 int radeon_ib_schedule (struct radeon_device*,struct radeon_ib*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  radeon_sync_resv (struct radeon_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_vm_set_pages (struct radeon_device*,struct radeon_ib*,scalar_t__,scalar_t__,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

int radeon_vm_update_page_directory(struct radeon_device *rdev,
				    struct radeon_vm *vm)
{
	struct radeon_bo *pd = vm->page_directory;
	uint64_t pd_addr = radeon_bo_gpu_offset(pd);
	uint32_t incr = RADEON_VM_PTE_COUNT * 8;
	uint64_t last_pde = ~0, last_pt = ~0;
	unsigned count = 0, pt_idx, ndw;
	struct radeon_ib ib;
	int r;

	/* padding, etc. */
	ndw = 64;

	/* assume the worst case */
	ndw += vm->max_pde_used * 6;

	/* update too big for an IB */
	if (ndw > 0xfffff)
		return -ENOMEM;

	r = radeon_ib_get(rdev, R600_RING_TYPE_DMA_INDEX, &ib, NULL, ndw * 4);
	if (r)
		return r;
	ib.length_dw = 0;

	/* walk over the address space and update the page directory */
	for (pt_idx = 0; pt_idx <= vm->max_pde_used; ++pt_idx) {
		struct radeon_bo *bo = vm->page_tables[pt_idx].bo;
		uint64_t pde, pt;

		if (bo == NULL)
			continue;

		pt = radeon_bo_gpu_offset(bo);
		if (vm->page_tables[pt_idx].addr == pt)
			continue;
		vm->page_tables[pt_idx].addr = pt;

		pde = pd_addr + pt_idx * 8;
		if (((last_pde + 8 * count) != pde) ||
		    ((last_pt + incr * count) != pt)) {

			if (count) {
				radeon_vm_set_pages(rdev, &ib, last_pde,
						    last_pt, count, incr,
						    R600_PTE_VALID);
			}

			count = 1;
			last_pde = pde;
			last_pt = pt;
		} else {
			++count;
		}
	}

	if (count)
		radeon_vm_set_pages(rdev, &ib, last_pde, last_pt, count,
				    incr, R600_PTE_VALID);

	if (ib.length_dw != 0) {
		radeon_asic_vm_pad_ib(rdev, &ib);

		radeon_sync_resv(rdev, &ib.sync, pd->tbo.base.resv, true);
		WARN_ON(ib.length_dw > ndw);
		r = radeon_ib_schedule(rdev, &ib, NULL, false);
		if (r) {
			radeon_ib_free(rdev, &ib);
			return r;
		}
		ib.fence->is_vm_update = true;
		radeon_bo_fence(pd, ib.fence, false);
	}
	radeon_ib_free(rdev, &ib);

	return 0;
}