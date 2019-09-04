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
typedef  size_t u16 ;
struct device {int dummy; } ;
struct dev_table_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * amd_iommu_dev_table ; 
 int /*<<< orphan*/ ** amd_iommu_rlookup_table ; 
 size_t get_alias (struct device*) ; 
 int get_device_id (struct device*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void iommu_ignore_device(struct device *dev)
{
	u16 alias;
	int devid;

	devid = get_device_id(dev);
	if (devid < 0)
		return;

	alias = get_alias(dev);

	memset(&amd_iommu_dev_table[devid], 0, sizeof(struct dev_table_entry));
	memset(&amd_iommu_dev_table[alias], 0, sizeof(struct dev_table_entry));

	amd_iommu_rlookup_table[devid] = NULL;
	amd_iommu_rlookup_table[alias] = NULL;
}