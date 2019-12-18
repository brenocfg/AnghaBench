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
struct omap_iommu_domain {int num_iommus; int /*<<< orphan*/  lock; struct device* dev; struct omap_iommu_device* iommus; } ;
struct omap_iommu_device {struct omap_iommu* iommu_dev; int /*<<< orphan*/  pgtable; } ;
struct omap_iommu_arch_data {struct omap_iommu* iommu_dev; } ;
struct omap_iommu {struct iommu_domain* domain; } ;
struct iommu_domain {int dummy; } ;
struct TYPE_2__ {struct omap_iommu_arch_data* iommu; } ;
struct device {TYPE_1__ archdata; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int omap_iommu_attach (struct omap_iommu*,int /*<<< orphan*/ ) ; 
 int omap_iommu_attach_init (struct device*,struct omap_iommu_domain*) ; 
 int /*<<< orphan*/  omap_iommu_detach (struct omap_iommu*) ; 
 int /*<<< orphan*/  omap_iommu_detach_fini (struct omap_iommu_domain*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct omap_iommu_domain* to_omap_domain (struct iommu_domain*) ; 

__attribute__((used)) static int
omap_iommu_attach_dev(struct iommu_domain *domain, struct device *dev)
{
	struct omap_iommu_domain *omap_domain = to_omap_domain(domain);
	struct omap_iommu_arch_data *arch_data = dev->archdata.iommu;
	struct omap_iommu_device *iommu;
	struct omap_iommu *oiommu;
	int ret = 0;
	int i;

	if (!arch_data || !arch_data->iommu_dev) {
		dev_err(dev, "device doesn't have an associated iommu\n");
		return -EINVAL;
	}

	spin_lock(&omap_domain->lock);

	/* only a single client device can be attached to a domain */
	if (omap_domain->dev) {
		dev_err(dev, "iommu domain is already attached\n");
		ret = -EBUSY;
		goto out;
	}

	ret = omap_iommu_attach_init(dev, omap_domain);
	if (ret) {
		dev_err(dev, "failed to allocate required iommu data %d\n",
			ret);
		goto init_fail;
	}

	iommu = omap_domain->iommus;
	for (i = 0; i < omap_domain->num_iommus; i++, iommu++, arch_data++) {
		/* configure and enable the omap iommu */
		oiommu = arch_data->iommu_dev;
		ret = omap_iommu_attach(oiommu, iommu->pgtable);
		if (ret) {
			dev_err(dev, "can't get omap iommu: %d\n", ret);
			goto attach_fail;
		}

		oiommu->domain = domain;
		iommu->iommu_dev = oiommu;
	}

	omap_domain->dev = dev;

	goto out;

attach_fail:
	while (i--) {
		iommu--;
		arch_data--;
		oiommu = iommu->iommu_dev;
		omap_iommu_detach(oiommu);
		iommu->iommu_dev = NULL;
		oiommu->domain = NULL;
	}
init_fail:
	omap_iommu_detach_fini(omap_domain);
out:
	spin_unlock(&omap_domain->lock);
	return ret;
}