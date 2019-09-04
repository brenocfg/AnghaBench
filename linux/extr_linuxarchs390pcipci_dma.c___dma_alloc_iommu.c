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
struct zpci_dev {unsigned long start_dma; int /*<<< orphan*/  iommu_pages; int /*<<< orphan*/  iommu_bitmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned long ALIGN (scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ dma_get_seg_boundary (struct device*) ; 
 unsigned long iommu_area_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_pci_dev (struct device*) ; 
 struct zpci_dev* to_zpci (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long __dma_alloc_iommu(struct device *dev,
				       unsigned long start, int size)
{
	struct zpci_dev *zdev = to_zpci(to_pci_dev(dev));
	unsigned long boundary_size;

	boundary_size = ALIGN(dma_get_seg_boundary(dev) + 1,
			      PAGE_SIZE) >> PAGE_SHIFT;
	return iommu_area_alloc(zdev->iommu_bitmap, zdev->iommu_pages,
				start, size, zdev->start_dma >> PAGE_SHIFT,
				boundary_size, 0);
}