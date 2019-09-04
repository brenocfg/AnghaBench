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
struct TYPE_2__ {int /*<<< orphan*/ * page; int /*<<< orphan*/  addr; } ;
struct radeon_device {TYPE_1__ dummy_page; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void radeon_dummy_page_fini(struct radeon_device *rdev)
{
	if (rdev->dummy_page.page == NULL)
		return;
	pci_unmap_page(rdev->pdev, rdev->dummy_page.addr,
			PAGE_SIZE, PCI_DMA_BIDIRECTIONAL);
	__free_page(rdev->dummy_page.page);
	rdev->dummy_page.page = NULL;
}