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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct amd_iommu {int /*<<< orphan*/  features; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct amd_iommu* dev_to_amd_iommu (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t amd_iommu_show_features(struct device *dev,
				       struct device_attribute *attr,
				       char *buf)
{
	struct amd_iommu *iommu = dev_to_amd_iommu(dev);
	return sprintf(buf, "%llx\n", iommu->features);
}