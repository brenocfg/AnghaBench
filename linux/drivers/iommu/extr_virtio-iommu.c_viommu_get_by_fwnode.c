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
struct viommu_dev {int dummy; } ;
struct fwnode_handle {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct viommu_dev* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 TYPE_2__* dev_to_virtio (struct device*) ; 
 struct device* driver_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct fwnode_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  viommu_match_node ; 
 TYPE_1__ virtio_iommu_drv ; 

__attribute__((used)) static struct viommu_dev *viommu_get_by_fwnode(struct fwnode_handle *fwnode)
{
	struct device *dev = driver_find_device(&virtio_iommu_drv.driver, NULL,
						fwnode, viommu_match_node);
	put_device(dev);

	return dev ? dev_to_virtio(dev)->priv : NULL;
}