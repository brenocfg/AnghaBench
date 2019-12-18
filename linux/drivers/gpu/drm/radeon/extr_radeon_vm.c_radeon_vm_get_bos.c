#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct radeon_vm {int max_pde_used; TYPE_1__* page_tables; TYPE_2__* page_directory; } ;
struct radeon_device {int dummy; } ;
struct TYPE_6__ {int num_shared; int /*<<< orphan*/  head; int /*<<< orphan*/ * bo; } ;
struct radeon_bo_list {TYPE_3__ tv; scalar_t__ tiling_flags; TYPE_2__* robj; void* allowed_domains; void* preferred_domains; } ;
struct list_head {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  tbo; } ;
struct TYPE_4__ {TYPE_2__* bo; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* RADEON_GEM_DOMAIN_VRAM ; 
 struct radeon_bo_list* kvmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 

struct radeon_bo_list *radeon_vm_get_bos(struct radeon_device *rdev,
					  struct radeon_vm *vm,
					  struct list_head *head)
{
	struct radeon_bo_list *list;
	unsigned i, idx;

	list = kvmalloc_array(vm->max_pde_used + 2,
			     sizeof(struct radeon_bo_list), GFP_KERNEL);
	if (!list)
		return NULL;

	/* add the vm page table to the list */
	list[0].robj = vm->page_directory;
	list[0].preferred_domains = RADEON_GEM_DOMAIN_VRAM;
	list[0].allowed_domains = RADEON_GEM_DOMAIN_VRAM;
	list[0].tv.bo = &vm->page_directory->tbo;
	list[0].tv.num_shared = 1;
	list[0].tiling_flags = 0;
	list_add(&list[0].tv.head, head);

	for (i = 0, idx = 1; i <= vm->max_pde_used; i++) {
		if (!vm->page_tables[i].bo)
			continue;

		list[idx].robj = vm->page_tables[i].bo;
		list[idx].preferred_domains = RADEON_GEM_DOMAIN_VRAM;
		list[idx].allowed_domains = RADEON_GEM_DOMAIN_VRAM;
		list[idx].tv.bo = &list[idx].robj->tbo;
		list[idx].tv.num_shared = 1;
		list[idx].tiling_flags = 0;
		list_add(&list[idx++].tv.head, head);
	}

	return list;
}