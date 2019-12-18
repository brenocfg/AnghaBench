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
struct qcom_iommu_dev {unsigned int num_ctxs; } ;
struct platform_device {int dummy; } ;
struct of_phandle_args {unsigned int* args; int args_count; TYPE_1__* np; } ;
struct iommu_fwspec {struct qcom_iommu_dev* iommu_priv; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  full_name; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 struct iommu_fwspec* dev_iommu_fwspec_get (struct device*) ; 
 int iommu_fwspec_add_ids (struct device*,unsigned int*,int) ; 
 struct platform_device* of_find_device_by_node (TYPE_1__*) ; 
 struct qcom_iommu_dev* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int qcom_iommu_of_xlate(struct device *dev, struct of_phandle_args *args)
{
	struct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	struct qcom_iommu_dev *qcom_iommu;
	struct platform_device *iommu_pdev;
	unsigned asid = args->args[0];

	if (args->args_count != 1) {
		dev_err(dev, "incorrect number of iommu params found for %s "
			"(found %d, expected 1)\n",
			args->np->full_name, args->args_count);
		return -EINVAL;
	}

	iommu_pdev = of_find_device_by_node(args->np);
	if (WARN_ON(!iommu_pdev))
		return -EINVAL;

	qcom_iommu = platform_get_drvdata(iommu_pdev);

	/* make sure the asid specified in dt is valid, so we don't have
	 * to sanity check this elsewhere, since 'asid - 1' is used to
	 * index into qcom_iommu->ctxs:
	 */
	if (WARN_ON(asid < 1) ||
	    WARN_ON(asid > qcom_iommu->num_ctxs))
		return -EINVAL;

	if (!fwspec->iommu_priv) {
		fwspec->iommu_priv = qcom_iommu;
	} else {
		/* make sure devices iommus dt node isn't referring to
		 * multiple different iommu devices.  Multiple context
		 * banks are ok, but multiple devices are not:
		 */
		if (WARN_ON(qcom_iommu != fwspec->iommu_priv))
			return -EINVAL;
	}

	return iommu_fwspec_add_ids(dev, &asid, 1);
}