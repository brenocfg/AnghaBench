#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vfio_pci_fill_info {size_t cur; size_t max; TYPE_1__* devices; } ;
struct pci_dev {int /*<<< orphan*/  devfn; TYPE_2__* bus; int /*<<< orphan*/  dev; } ;
struct iommu_group {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  number; } ;
struct TYPE_3__ {int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; int /*<<< orphan*/  segment; int /*<<< orphan*/  group_id; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EPERM ; 
 struct iommu_group* iommu_group_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_group_id (struct iommu_group*) ; 
 int /*<<< orphan*/  iommu_group_put (struct iommu_group*) ; 
 int /*<<< orphan*/  pci_domain_nr (TYPE_2__*) ; 

__attribute__((used)) static int vfio_pci_fill_devs(struct pci_dev *pdev, void *data)
{
	struct vfio_pci_fill_info *fill = data;
	struct iommu_group *iommu_group;

	if (fill->cur == fill->max)
		return -EAGAIN; /* Something changed, try again */

	iommu_group = iommu_group_get(&pdev->dev);
	if (!iommu_group)
		return -EPERM; /* Cannot reset non-isolated devices */

	fill->devices[fill->cur].group_id = iommu_group_id(iommu_group);
	fill->devices[fill->cur].segment = pci_domain_nr(pdev->bus);
	fill->devices[fill->cur].bus = pdev->bus->number;
	fill->devices[fill->cur].devfn = pdev->devfn;
	fill->cur++;
	iommu_group_put(iommu_group);
	return 0;
}