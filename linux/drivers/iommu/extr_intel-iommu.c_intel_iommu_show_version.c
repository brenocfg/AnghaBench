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
typedef  int /*<<< orphan*/  u32 ;
struct intel_iommu {scalar_t__ reg; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int DMAR_VER_MAJOR (int /*<<< orphan*/ ) ; 
 int DMAR_VER_MINOR (int /*<<< orphan*/ ) ; 
 scalar_t__ DMAR_VER_REG ; 
 struct intel_iommu* dev_to_intel_iommu (struct device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 

__attribute__((used)) static ssize_t intel_iommu_show_version(struct device *dev,
					struct device_attribute *attr,
					char *buf)
{
	struct intel_iommu *iommu = dev_to_intel_iommu(dev);
	u32 ver = readl(iommu->reg + DMAR_VER_REG);
	return sprintf(buf, "%d:%d\n",
		       DMAR_VER_MAJOR(ver), DMAR_VER_MINOR(ver));
}