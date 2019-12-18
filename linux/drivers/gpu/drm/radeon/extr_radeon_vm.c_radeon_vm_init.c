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
struct radeon_vm_pt {int dummy; } ;
struct radeon_vm {int /*<<< orphan*/ * page_directory; int /*<<< orphan*/ * page_tables; int /*<<< orphan*/  cleared; int /*<<< orphan*/  freed; int /*<<< orphan*/  invalidated; int /*<<< orphan*/  status_lock; int /*<<< orphan*/  va; int /*<<< orphan*/  mutex; TYPE_1__* ids; int /*<<< orphan*/ * ib_bo_va; } ;
struct radeon_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * last_id_use; int /*<<< orphan*/ * flushed_updates; scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RADEON_GEM_DOMAIN_VRAM ; 
 int RADEON_NUM_RINGS ; 
 int /*<<< orphan*/  RADEON_VM_PTB_ALIGN_SIZE ; 
 int RADEON_VM_PTE_COUNT ; 
 int /*<<< orphan*/  RB_ROOT_CACHED ; 
 int /*<<< orphan*/ * kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int radeon_bo_create (struct radeon_device*,unsigned int,unsigned int const,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  radeon_bo_unref (int /*<<< orphan*/ **) ; 
 int radeon_vm_clear_bo (struct radeon_device*,int /*<<< orphan*/ *) ; 
 unsigned int radeon_vm_directory_size (struct radeon_device*) ; 
 unsigned int radeon_vm_num_pdes (struct radeon_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int radeon_vm_init(struct radeon_device *rdev, struct radeon_vm *vm)
{
	const unsigned align = min(RADEON_VM_PTB_ALIGN_SIZE,
		RADEON_VM_PTE_COUNT * 8);
	unsigned pd_size, pd_entries, pts_size;
	int i, r;

	vm->ib_bo_va = NULL;
	for (i = 0; i < RADEON_NUM_RINGS; ++i) {
		vm->ids[i].id = 0;
		vm->ids[i].flushed_updates = NULL;
		vm->ids[i].last_id_use = NULL;
	}
	mutex_init(&vm->mutex);
	vm->va = RB_ROOT_CACHED;
	spin_lock_init(&vm->status_lock);
	INIT_LIST_HEAD(&vm->invalidated);
	INIT_LIST_HEAD(&vm->freed);
	INIT_LIST_HEAD(&vm->cleared);

	pd_size = radeon_vm_directory_size(rdev);
	pd_entries = radeon_vm_num_pdes(rdev);

	/* allocate page table array */
	pts_size = pd_entries * sizeof(struct radeon_vm_pt);
	vm->page_tables = kzalloc(pts_size, GFP_KERNEL);
	if (vm->page_tables == NULL) {
		DRM_ERROR("Cannot allocate memory for page table array\n");
		return -ENOMEM;
	}

	r = radeon_bo_create(rdev, pd_size, align, true,
			     RADEON_GEM_DOMAIN_VRAM, 0, NULL,
			     NULL, &vm->page_directory);
	if (r)
		return r;

	r = radeon_vm_clear_bo(rdev, vm->page_directory);
	if (r) {
		radeon_bo_unref(&vm->page_directory);
		vm->page_directory = NULL;
		return r;
	}

	return 0;
}