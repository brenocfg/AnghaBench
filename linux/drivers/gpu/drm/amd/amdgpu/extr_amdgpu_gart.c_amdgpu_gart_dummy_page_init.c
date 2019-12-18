#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct TYPE_7__ {TYPE_1__* glob; } ;
struct TYPE_8__ {TYPE_2__ bdev; } ;
struct amdgpu_device {scalar_t__ dummy_page_addr; TYPE_4__* pdev; TYPE_3__ mman; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {struct page* dummy_read_page; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ pci_dma_mapping_error (TYPE_4__*,scalar_t__) ; 
 scalar_t__ pci_map_page (TYPE_4__*,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amdgpu_gart_dummy_page_init(struct amdgpu_device *adev)
{
	struct page *dummy_page = adev->mman.bdev.glob->dummy_read_page;

	if (adev->dummy_page_addr)
		return 0;
	adev->dummy_page_addr = pci_map_page(adev->pdev, dummy_page, 0,
					     PAGE_SIZE, PCI_DMA_BIDIRECTIONAL);
	if (pci_dma_mapping_error(adev->pdev, adev->dummy_page_addr)) {
		dev_err(&adev->pdev->dev, "Failed to DMA MAP the dummy page\n");
		adev->dummy_page_addr = 0;
		return -ENOMEM;
	}
	return 0;
}