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
struct platform_device {int dummy; } ;
struct of_phandle_args {int args_count; int /*<<< orphan*/  args; int /*<<< orphan*/  np; } ;
struct iommu_fwspec {scalar_t__ iommu_priv; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct iommu_fwspec* dev_iommu_fwspec_get (struct device*) ; 
 int iommu_fwspec_add_ids (struct device*,int /*<<< orphan*/ ,int) ; 
 struct platform_device* of_find_device_by_node (int /*<<< orphan*/ ) ; 
 scalar_t__ platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mtk_iommu_of_xlate(struct device *dev, struct of_phandle_args *args)
{
	struct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	struct platform_device *m4updev;

	if (args->args_count != 1) {
		dev_err(dev, "invalid #iommu-cells(%d) property for IOMMU\n",
			args->args_count);
		return -EINVAL;
	}

	if (!fwspec->iommu_priv) {
		/* Get the m4u device */
		m4updev = of_find_device_by_node(args->np);
		if (WARN_ON(!m4updev))
			return -EINVAL;

		fwspec->iommu_priv = platform_get_drvdata(m4updev);
	}

	return iommu_fwspec_add_ids(dev, args->args, 1);
}