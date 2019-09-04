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
struct zpci_dev {unsigned long start_dma; int /*<<< orphan*/  iommu_bitmap_lock; int /*<<< orphan*/  lazy_bitmap; int /*<<< orphan*/  iommu_bitmap; } ;
struct device {int dummy; } ;
typedef  unsigned long dma_addr_t ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  bitmap_clear (int /*<<< orphan*/ ,unsigned long,int) ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,unsigned long,int) ; 
 scalar_t__ s390_iommu_strict ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  to_pci_dev (struct device*) ; 
 struct zpci_dev* to_zpci (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dma_free_address(struct device *dev, dma_addr_t dma_addr, int size)
{
	struct zpci_dev *zdev = to_zpci(to_pci_dev(dev));
	unsigned long flags, offset;

	offset = (dma_addr - zdev->start_dma) >> PAGE_SHIFT;

	spin_lock_irqsave(&zdev->iommu_bitmap_lock, flags);
	if (!zdev->iommu_bitmap)
		goto out;

	if (s390_iommu_strict)
		bitmap_clear(zdev->iommu_bitmap, offset, size);
	else
		bitmap_set(zdev->lazy_bitmap, offset, size);

out:
	spin_unlock_irqrestore(&zdev->iommu_bitmap_lock, flags);
}