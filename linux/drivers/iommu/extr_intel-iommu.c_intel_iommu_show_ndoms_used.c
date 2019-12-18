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
struct intel_iommu {int /*<<< orphan*/  cap; int /*<<< orphan*/  domain_ids; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int bitmap_weight (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_ndoms (int /*<<< orphan*/ ) ; 
 struct intel_iommu* dev_to_intel_iommu (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t intel_iommu_show_ndoms_used(struct device *dev,
					   struct device_attribute *attr,
					   char *buf)
{
	struct intel_iommu *iommu = dev_to_intel_iommu(dev);
	return sprintf(buf, "%d\n", bitmap_weight(iommu->domain_ids,
						  cap_ndoms(iommu->cap)));
}