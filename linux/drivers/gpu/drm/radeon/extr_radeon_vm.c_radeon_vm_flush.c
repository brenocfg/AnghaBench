#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct radeon_vm_id {scalar_t__ pd_gpu_addr; int /*<<< orphan*/  id; scalar_t__ flushed_updates; } ;
struct radeon_vm {struct radeon_vm_id* ids; int /*<<< orphan*/  page_directory; } ;
struct radeon_fence {int dummy; } ;
struct radeon_device {int /*<<< orphan*/ * ring; } ;

/* Variables and functions */
 scalar_t__ radeon_bo_gpu_offset (int /*<<< orphan*/ ) ; 
 scalar_t__ radeon_fence_is_earlier (scalar_t__,struct radeon_fence*) ; 
 scalar_t__ radeon_fence_ref (struct radeon_fence*) ; 
 int /*<<< orphan*/  radeon_fence_unref (scalar_t__*) ; 
 int /*<<< orphan*/  radeon_ring_vm_flush (struct radeon_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  trace_radeon_vm_flush (scalar_t__,int,int /*<<< orphan*/ ) ; 

void radeon_vm_flush(struct radeon_device *rdev,
		     struct radeon_vm *vm,
		     int ring, struct radeon_fence *updates)
{
	uint64_t pd_addr = radeon_bo_gpu_offset(vm->page_directory);
	struct radeon_vm_id *vm_id = &vm->ids[ring];

	if (pd_addr != vm_id->pd_gpu_addr || !vm_id->flushed_updates ||
	    radeon_fence_is_earlier(vm_id->flushed_updates, updates)) {

		trace_radeon_vm_flush(pd_addr, ring, vm->ids[ring].id);
		radeon_fence_unref(&vm_id->flushed_updates);
		vm_id->flushed_updates = radeon_fence_ref(updates);
		vm_id->pd_gpu_addr = pd_addr;
		radeon_ring_vm_flush(rdev, &rdev->ring[ring],
				     vm_id->id, vm_id->pd_gpu_addr);

	}
}