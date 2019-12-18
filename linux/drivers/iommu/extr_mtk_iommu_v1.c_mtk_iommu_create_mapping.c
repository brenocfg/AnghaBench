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
struct platform_device {int dummy; } ;
struct of_phandle_args {int args_count; int /*<<< orphan*/  args; TYPE_2__* np; } ;
struct mtk_iommu_data {struct device* dev; } ;
struct iommu_fwspec {struct mtk_iommu_data* iommu_priv; int /*<<< orphan*/ * ops; } ;
struct dma_iommu_mapping {int dummy; } ;
struct TYPE_3__ {struct dma_iommu_mapping* iommu; } ;
struct device {TYPE_1__ archdata; } ;
struct TYPE_4__ {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct dma_iommu_mapping*) ; 
 int PTR_ERR (struct dma_iommu_mapping*) ; 
 scalar_t__ WARN_ON (int) ; 
 struct dma_iommu_mapping* arm_iommu_create_mapping (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct iommu_fwspec* dev_iommu_fwspec_get (struct device*) ; 
 int iommu_fwspec_add_ids (struct device*,int /*<<< orphan*/ ,int) ; 
 int iommu_fwspec_init (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_iommu_ops ; 
 struct platform_device* of_find_device_by_node (TYPE_2__*) ; 
 int /*<<< orphan*/  platform_bus_type ; 
 struct mtk_iommu_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mtk_iommu_create_mapping(struct device *dev,
				    struct of_phandle_args *args)
{
	struct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	struct mtk_iommu_data *data;
	struct platform_device *m4updev;
	struct dma_iommu_mapping *mtk_mapping;
	struct device *m4udev;
	int ret;

	if (args->args_count != 1) {
		dev_err(dev, "invalid #iommu-cells(%d) property for IOMMU\n",
			args->args_count);
		return -EINVAL;
	}

	if (!fwspec) {
		ret = iommu_fwspec_init(dev, &args->np->fwnode, &mtk_iommu_ops);
		if (ret)
			return ret;
		fwspec = dev_iommu_fwspec_get(dev);
	} else if (dev_iommu_fwspec_get(dev)->ops != &mtk_iommu_ops) {
		return -EINVAL;
	}

	if (!fwspec->iommu_priv) {
		/* Get the m4u device */
		m4updev = of_find_device_by_node(args->np);
		if (WARN_ON(!m4updev))
			return -EINVAL;

		fwspec->iommu_priv = platform_get_drvdata(m4updev);
	}

	ret = iommu_fwspec_add_ids(dev, args->args, 1);
	if (ret)
		return ret;

	data = fwspec->iommu_priv;
	m4udev = data->dev;
	mtk_mapping = m4udev->archdata.iommu;
	if (!mtk_mapping) {
		/* MTK iommu support 4GB iova address space. */
		mtk_mapping = arm_iommu_create_mapping(&platform_bus_type,
						0, 1ULL << 32);
		if (IS_ERR(mtk_mapping))
			return PTR_ERR(mtk_mapping);

		m4udev->archdata.iommu = mtk_mapping;
	}

	return 0;
}