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
struct iommu_table {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 struct iommu_table* get_iommu_table_base (struct device*) ; 
 int /*<<< orphan*/  iommu_tce_table_put (struct iommu_table*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_vio_dev (struct device*) ; 

__attribute__((used)) static void vio_dev_release(struct device *dev)
{
	struct iommu_table *tbl = get_iommu_table_base(dev);

	if (tbl)
		iommu_tce_table_put(tbl);
	of_node_put(dev->of_node);
	kfree(to_vio_dev(dev));
}