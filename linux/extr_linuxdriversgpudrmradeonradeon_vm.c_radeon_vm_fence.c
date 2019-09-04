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
struct radeon_vm {TYPE_2__* ids; } ;
struct radeon_fence {size_t ring; } ;
struct TYPE_3__ {void** active; } ;
struct radeon_device {TYPE_1__ vm_manager; } ;
struct TYPE_4__ {unsigned int id; void* last_id_use; } ;

/* Variables and functions */
 void* radeon_fence_ref (struct radeon_fence*) ; 
 int /*<<< orphan*/  radeon_fence_unref (void**) ; 

void radeon_vm_fence(struct radeon_device *rdev,
		     struct radeon_vm *vm,
		     struct radeon_fence *fence)
{
	unsigned vm_id = vm->ids[fence->ring].id;

	radeon_fence_unref(&rdev->vm_manager.active[vm_id]);
	rdev->vm_manager.active[vm_id] = radeon_fence_ref(fence);

	radeon_fence_unref(&vm->ids[fence->ring].last_id_use);
	vm->ids[fence->ring].last_id_use = radeon_fence_ref(fence);
}