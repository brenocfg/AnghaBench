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
struct amd_iommu {int index; void* debugfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_NAME_LEN ; 
 void* amd_iommu_debugfs ; 
 int /*<<< orphan*/  amd_iommu_debugfs_lock ; 
 void* debugfs_create_dir (char*,void*) ; 
 void* iommu_debugfs_dir ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

void amd_iommu_debugfs_setup(struct amd_iommu *iommu)
{
	char name[MAX_NAME_LEN + 1];

	mutex_lock(&amd_iommu_debugfs_lock);
	if (!amd_iommu_debugfs)
		amd_iommu_debugfs = debugfs_create_dir("amd",
						       iommu_debugfs_dir);
	mutex_unlock(&amd_iommu_debugfs_lock);

	snprintf(name, MAX_NAME_LEN, "iommu%02d", iommu->index);
	iommu->debugfs = debugfs_create_dir(name, amd_iommu_debugfs);
}