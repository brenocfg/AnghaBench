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
struct TYPE_2__ {int table_size; scalar_t__ table_addr; int /*<<< orphan*/ * ptr; } ;
struct radeon_device {scalar_t__ family; TYPE_1__ gart; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 scalar_t__ CHIP_RS400 ; 
 scalar_t__ CHIP_RS480 ; 
 scalar_t__ CHIP_RS690 ; 
 scalar_t__ CHIP_RS740 ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,void*,scalar_t__) ; 
 int /*<<< orphan*/  set_memory_wb (unsigned long,int) ; 

void radeon_gart_table_ram_free(struct radeon_device *rdev)
{
	if (rdev->gart.ptr == NULL) {
		return;
	}
#ifdef CONFIG_X86
	if (rdev->family == CHIP_RS400 || rdev->family == CHIP_RS480 ||
	    rdev->family == CHIP_RS690 || rdev->family == CHIP_RS740) {
		set_memory_wb((unsigned long)rdev->gart.ptr,
			      rdev->gart.table_size >> PAGE_SHIFT);
	}
#endif
	pci_free_consistent(rdev->pdev, rdev->gart.table_size,
			    (void *)rdev->gart.ptr,
			    rdev->gart.table_addr);
	rdev->gart.ptr = NULL;
	rdev->gart.table_addr = 0;
}