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
struct amdgpu_vm_bo_base {TYPE_1__* vm; int /*<<< orphan*/  vm_status; } ;
struct TYPE_2__ {int /*<<< orphan*/  invalidated_lock; int /*<<< orphan*/  invalidated; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void amdgpu_vm_bo_invalidated(struct amdgpu_vm_bo_base *vm_bo)
{
	spin_lock(&vm_bo->vm->invalidated_lock);
	list_move(&vm_bo->vm_status, &vm_bo->vm->invalidated);
	spin_unlock(&vm_bo->vm->invalidated_lock);
}