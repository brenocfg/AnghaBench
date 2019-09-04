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
typedef  size_t uint64_t ;
struct TYPE_2__ {size_t* pages_entry; } ;
struct radeon_device {TYPE_1__ gart; } ;

/* Variables and functions */
 size_t RADEON_GPU_PAGE_MASK ; 
 size_t RADEON_GPU_PAGE_SHIFT ; 

uint64_t radeon_vm_map_gart(struct radeon_device *rdev, uint64_t addr)
{
	uint64_t result;

	/* page table offset */
	result = rdev->gart.pages_entry[addr >> RADEON_GPU_PAGE_SHIFT];
	result &= ~RADEON_GPU_PAGE_MASK;

	return result;
}