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
struct TYPE_3__ {TYPE_2__* bo; int /*<<< orphan*/  vm_status; } ;
struct amdgpu_vm_pt {int /*<<< orphan*/ * entries; TYPE_1__ base; } ;
struct TYPE_4__ {struct TYPE_4__* shadow; int /*<<< orphan*/ * vm_bo; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_unref (TYPE_2__**) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void amdgpu_vm_free_table(struct amdgpu_vm_pt *entry)
{
	if (entry->base.bo) {
		entry->base.bo->vm_bo = NULL;
		list_del(&entry->base.vm_status);
		amdgpu_bo_unref(&entry->base.bo->shadow);
		amdgpu_bo_unref(&entry->base.bo);
	}
	kvfree(entry->entries);
	entry->entries = NULL;
}