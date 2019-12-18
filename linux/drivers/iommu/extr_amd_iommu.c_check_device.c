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
struct device {int /*<<< orphan*/  dma_mask; } ;

/* Variables and functions */
 int amd_iommu_last_bdf ; 
 int /*<<< orphan*/ ** amd_iommu_rlookup_table ; 
 int get_device_id (struct device*) ; 

__attribute__((used)) static bool check_device(struct device *dev)
{
	int devid;

	if (!dev || !dev->dma_mask)
		return false;

	devid = get_device_id(dev);
	if (devid < 0)
		return false;

	/* Out of our scope? */
	if (devid > amd_iommu_last_bdf)
		return false;

	if (amd_iommu_rlookup_table[devid] == NULL)
		return false;

	return true;
}