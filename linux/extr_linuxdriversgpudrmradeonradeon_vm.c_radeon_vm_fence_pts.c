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
typedef  int uint64_t ;
struct radeon_vm {TYPE_1__* page_tables; } ;
struct radeon_fence {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bo; } ;

/* Variables and functions */
 int /*<<< orphan*/  radeon_bo_fence (int /*<<< orphan*/ ,struct radeon_fence*,int) ; 
 int radeon_vm_block_size ; 

__attribute__((used)) static void radeon_vm_fence_pts(struct radeon_vm *vm,
				uint64_t start, uint64_t end,
				struct radeon_fence *fence)
{
	unsigned i;

	start >>= radeon_vm_block_size;
	end = (end - 1) >> radeon_vm_block_size;

	for (i = start; i <= end; ++i)
		radeon_bo_fence(vm->page_tables[i].bo, fence, true);
}