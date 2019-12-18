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
typedef  int /*<<< orphan*/  uint64_t ;
struct amdgpu_vm_pt_cursor {int /*<<< orphan*/  level; int /*<<< orphan*/ * entry; int /*<<< orphan*/ * parent; int /*<<< orphan*/  pfn; } ;
struct amdgpu_vm {int /*<<< orphan*/  root; } ;
struct TYPE_2__ {int /*<<< orphan*/  root_level; } ;
struct amdgpu_device {TYPE_1__ vm_manager; } ;

/* Variables and functions */

__attribute__((used)) static void amdgpu_vm_pt_start(struct amdgpu_device *adev,
			       struct amdgpu_vm *vm, uint64_t start,
			       struct amdgpu_vm_pt_cursor *cursor)
{
	cursor->pfn = start;
	cursor->parent = NULL;
	cursor->entry = &vm->root;
	cursor->level = adev->vm_manager.root_level;
}