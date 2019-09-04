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
struct amdgpu_device {scalar_t__ dummy_page_addr; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void amdgpu_gart_dummy_page_fini(struct amdgpu_device *adev)
{
	if (!adev->dummy_page_addr)
		return;
	pci_unmap_page(adev->pdev, adev->dummy_page_addr,
		       PAGE_SIZE, PCI_DMA_BIDIRECTIONAL);
	adev->dummy_page_addr = 0;
}