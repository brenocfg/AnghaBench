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
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DART_U4_BYPASS_BASE ; 
 scalar_t__ dart_is_u4 ; 
 int /*<<< orphan*/  iommu_table_dart ; 
 int /*<<< orphan*/  set_dma_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_iommu_table_base (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pci_dma_dev_setup_dart(struct pci_dev *dev)
{
	if (dart_is_u4)
		set_dma_offset(&dev->dev, DART_U4_BYPASS_BASE);
	set_iommu_table_base(&dev->dev, &iommu_table_dart);
}