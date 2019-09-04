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
typedef  int u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct iommu_dev_data {int errata; } ;

/* Variables and functions */
 struct iommu_dev_data* get_dev_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool pdev_pri_erratum(struct pci_dev *pdev, u32 erratum)
{
	struct iommu_dev_data *dev_data;

	dev_data = get_dev_data(&pdev->dev);

	return dev_data->errata & (1 << erratum) ? true : false;
}