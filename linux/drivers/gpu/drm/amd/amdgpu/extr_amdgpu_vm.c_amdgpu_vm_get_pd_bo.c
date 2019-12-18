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
struct list_head {int dummy; } ;
struct TYPE_6__ {TYPE_1__* bo; } ;
struct TYPE_7__ {TYPE_2__ base; } ;
struct amdgpu_vm {TYPE_3__ root; } ;
struct TYPE_8__ {int num_shared; int /*<<< orphan*/  head; int /*<<< orphan*/ * bo; } ;
struct amdgpu_bo_list_entry {TYPE_4__ tv; int /*<<< orphan*/ * user_pages; scalar_t__ priority; } ;
struct TYPE_5__ {int /*<<< orphan*/  tbo; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 

void amdgpu_vm_get_pd_bo(struct amdgpu_vm *vm,
			 struct list_head *validated,
			 struct amdgpu_bo_list_entry *entry)
{
	entry->priority = 0;
	entry->tv.bo = &vm->root.base.bo->tbo;
	/* One for the VM updates, one for TTM and one for the CS job */
	entry->tv.num_shared = 3;
	entry->user_pages = NULL;
	list_add(&entry->tv.head, validated);
}