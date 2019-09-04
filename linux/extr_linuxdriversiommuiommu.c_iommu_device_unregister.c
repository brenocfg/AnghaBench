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
struct iommu_device {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  iommu_device_lock ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void iommu_device_unregister(struct iommu_device *iommu)
{
	spin_lock(&iommu_device_lock);
	list_del(&iommu->list);
	spin_unlock(&iommu_device_lock);
}