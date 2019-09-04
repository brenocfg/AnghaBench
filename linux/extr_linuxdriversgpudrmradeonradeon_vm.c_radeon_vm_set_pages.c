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
typedef  int uint32_t ;
struct radeon_ib {int dummy; } ;
struct TYPE_2__ {int table_addr; } ;
struct radeon_device {TYPE_1__ gart; } ;

/* Variables and functions */
 int R600_PTE_GART_MASK ; 
 int R600_PTE_SYSTEM ; 
 int /*<<< orphan*/  radeon_asic_vm_copy_pages (struct radeon_device*,struct radeon_ib*,int,int,unsigned int) ; 
 int /*<<< orphan*/  radeon_asic_vm_set_pages (struct radeon_device*,struct radeon_ib*,int,int,unsigned int,int,int) ; 
 int /*<<< orphan*/  radeon_asic_vm_write_pages (struct radeon_device*,struct radeon_ib*,int,int,unsigned int,int,int) ; 
 int /*<<< orphan*/  trace_radeon_vm_set_page (int,int,unsigned int,int,int) ; 

__attribute__((used)) static void radeon_vm_set_pages(struct radeon_device *rdev,
				struct radeon_ib *ib,
				uint64_t pe,
				uint64_t addr, unsigned count,
				uint32_t incr, uint32_t flags)
{
	trace_radeon_vm_set_page(pe, addr, count, incr, flags);

	if ((flags & R600_PTE_GART_MASK) == R600_PTE_GART_MASK) {
		uint64_t src = rdev->gart.table_addr + (addr >> 12) * 8;
		radeon_asic_vm_copy_pages(rdev, ib, pe, src, count);

	} else if ((flags & R600_PTE_SYSTEM) || (count < 3)) {
		radeon_asic_vm_write_pages(rdev, ib, pe, addr,
					   count, incr, flags);

	} else {
		radeon_asic_vm_set_pages(rdev, ib, pe, addr,
					 count, incr, flags);
	}
}