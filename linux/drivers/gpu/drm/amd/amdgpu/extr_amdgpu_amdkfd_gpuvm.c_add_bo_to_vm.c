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
typedef  scalar_t__ uint64_t ;
struct list_head {int dummy; } ;
struct kgd_mem {int /*<<< orphan*/  mapping_flags; struct list_head bo_va_list; scalar_t__ va; struct amdgpu_bo* bo; } ;
struct kfd_bo_va_list {int /*<<< orphan*/  bo_list; int /*<<< orphan*/  bo_va; void* kgd_dev; int /*<<< orphan*/  pte_flags; scalar_t__ va; } ;
struct amdgpu_vm {int dummy; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_3__ {unsigned long size; } ;
struct TYPE_4__ {TYPE_1__ mem; } ;
struct amdgpu_bo {TYPE_2__ tbo; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  amdgpu_gmc_get_pte_flags (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_vm_bo_add (struct amdgpu_device*,struct amdgpu_vm*,struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_vm_bo_rmv (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct kfd_bo_va_list*) ; 
 struct kfd_bo_va_list* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,scalar_t__,struct amdgpu_vm*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int vm_validate_pt_pd_bos (struct amdgpu_vm*) ; 

__attribute__((used)) static int add_bo_to_vm(struct amdgpu_device *adev, struct kgd_mem *mem,
		struct amdgpu_vm *vm, bool is_aql,
		struct kfd_bo_va_list **p_bo_va_entry)
{
	int ret;
	struct kfd_bo_va_list *bo_va_entry;
	struct amdgpu_bo *bo = mem->bo;
	uint64_t va = mem->va;
	struct list_head *list_bo_va = &mem->bo_va_list;
	unsigned long bo_size = bo->tbo.mem.size;

	if (!va) {
		pr_err("Invalid VA when adding BO to VM\n");
		return -EINVAL;
	}

	if (is_aql)
		va += bo_size;

	bo_va_entry = kzalloc(sizeof(*bo_va_entry), GFP_KERNEL);
	if (!bo_va_entry)
		return -ENOMEM;

	pr_debug("\t add VA 0x%llx - 0x%llx to vm %p\n", va,
			va + bo_size, vm);

	/* Add BO to VM internal data structures*/
	bo_va_entry->bo_va = amdgpu_vm_bo_add(adev, vm, bo);
	if (!bo_va_entry->bo_va) {
		ret = -EINVAL;
		pr_err("Failed to add BO object to VM. ret == %d\n",
				ret);
		goto err_vmadd;
	}

	bo_va_entry->va = va;
	bo_va_entry->pte_flags = amdgpu_gmc_get_pte_flags(adev,
							 mem->mapping_flags);
	bo_va_entry->kgd_dev = (void *)adev;
	list_add(&bo_va_entry->bo_list, list_bo_va);

	if (p_bo_va_entry)
		*p_bo_va_entry = bo_va_entry;

	/* Allocate validate page tables if needed */
	ret = vm_validate_pt_pd_bos(vm);
	if (ret) {
		pr_err("validate_pt_pd_bos() failed\n");
		goto err_alloc_pts;
	}

	return 0;

err_alloc_pts:
	amdgpu_vm_bo_rmv(adev, bo_va_entry->bo_va);
	list_del(&bo_va_entry->bo_list);
err_vmadd:
	kfree(bo_va_entry);
	return ret;
}