#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct omap_iommu_arch_data {struct omap_iommu* iommu_dev; } ;
struct omap_iommu {int /*<<< orphan*/  iommu; } ;
struct iommu_group {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {struct omap_iommu_arch_data* iommu; } ;
struct device {TYPE_1__ archdata; int /*<<< orphan*/  of_node; } ;
typedef  int /*<<< orphan*/  phandle ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct iommu_group*) ; 
 int PTR_ERR (struct iommu_group*) ; 
 scalar_t__ WARN_ON (int) ; 
 int iommu_device_link (int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  iommu_device_unlink (int /*<<< orphan*/ *,struct device*) ; 
 struct iommu_group* iommu_group_get_for_dev (struct device*) ; 
 int /*<<< orphan*/  iommu_group_put (struct iommu_group*) ; 
 struct omap_iommu_arch_data* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct omap_iommu_arch_data*) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int) ; 
 int of_property_count_elems_of_size (int /*<<< orphan*/ ,char*,int) ; 
 struct omap_iommu* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int omap_iommu_add_device(struct device *dev)
{
	struct omap_iommu_arch_data *arch_data, *tmp;
	struct omap_iommu *oiommu;
	struct iommu_group *group;
	struct device_node *np;
	struct platform_device *pdev;
	int num_iommus, i;
	int ret;

	/*
	 * Allocate the archdata iommu structure for DT-based devices.
	 *
	 * TODO: Simplify this when removing non-DT support completely from the
	 * IOMMU users.
	 */
	if (!dev->of_node)
		return 0;

	/*
	 * retrieve the count of IOMMU nodes using phandle size as element size
	 * since #iommu-cells = 0 for OMAP
	 */
	num_iommus = of_property_count_elems_of_size(dev->of_node, "iommus",
						     sizeof(phandle));
	if (num_iommus < 0)
		return 0;

	arch_data = kcalloc(num_iommus + 1, sizeof(*arch_data), GFP_KERNEL);
	if (!arch_data)
		return -ENOMEM;

	for (i = 0, tmp = arch_data; i < num_iommus; i++, tmp++) {
		np = of_parse_phandle(dev->of_node, "iommus", i);
		if (!np) {
			kfree(arch_data);
			return -EINVAL;
		}

		pdev = of_find_device_by_node(np);
		if (WARN_ON(!pdev)) {
			of_node_put(np);
			kfree(arch_data);
			return -EINVAL;
		}

		oiommu = platform_get_drvdata(pdev);
		if (!oiommu) {
			of_node_put(np);
			kfree(arch_data);
			return -EINVAL;
		}

		tmp->iommu_dev = oiommu;

		of_node_put(np);
	}

	/*
	 * use the first IOMMU alone for the sysfs device linking.
	 * TODO: Evaluate if a single iommu_group needs to be
	 * maintained for both IOMMUs
	 */
	oiommu = arch_data->iommu_dev;
	ret = iommu_device_link(&oiommu->iommu, dev);
	if (ret) {
		kfree(arch_data);
		return ret;
	}

	dev->archdata.iommu = arch_data;

	/*
	 * IOMMU group initialization calls into omap_iommu_device_group, which
	 * needs a valid dev->archdata.iommu pointer
	 */
	group = iommu_group_get_for_dev(dev);
	if (IS_ERR(group)) {
		iommu_device_unlink(&oiommu->iommu, dev);
		dev->archdata.iommu = NULL;
		kfree(arch_data);
		return PTR_ERR(group);
	}
	iommu_group_put(group);

	return 0;
}