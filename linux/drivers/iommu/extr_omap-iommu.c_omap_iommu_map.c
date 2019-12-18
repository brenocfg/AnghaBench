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
typedef  size_t u32 ;
struct omap_iommu_domain {int num_iommus; struct omap_iommu_device* iommus; struct device* dev; } ;
struct omap_iommu_device {struct omap_iommu* iommu_dev; } ;
struct omap_iommu {int dummy; } ;
struct iotlb_entry {int dummy; } ;
struct iommu_domain {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 int bytes_to_iopgsz (size_t) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned long,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,size_t) ; 
 int /*<<< orphan*/  iopgtable_clear_entry (struct omap_iommu*,unsigned long) ; 
 int /*<<< orphan*/  iotlb_init_entry (struct iotlb_entry*,unsigned long,int /*<<< orphan*/ ,int) ; 
 size_t omap_iopgtable_store_entry (struct omap_iommu*,struct iotlb_entry*) ; 
 struct omap_iommu_domain* to_omap_domain (struct iommu_domain*) ; 

__attribute__((used)) static int omap_iommu_map(struct iommu_domain *domain, unsigned long da,
			  phys_addr_t pa, size_t bytes, int prot)
{
	struct omap_iommu_domain *omap_domain = to_omap_domain(domain);
	struct device *dev = omap_domain->dev;
	struct omap_iommu_device *iommu;
	struct omap_iommu *oiommu;
	struct iotlb_entry e;
	int omap_pgsz;
	u32 ret = -EINVAL;
	int i;

	omap_pgsz = bytes_to_iopgsz(bytes);
	if (omap_pgsz < 0) {
		dev_err(dev, "invalid size to map: %d\n", bytes);
		return -EINVAL;
	}

	dev_dbg(dev, "mapping da 0x%lx to pa %pa size 0x%x\n", da, &pa, bytes);

	iotlb_init_entry(&e, da, pa, omap_pgsz);

	iommu = omap_domain->iommus;
	for (i = 0; i < omap_domain->num_iommus; i++, iommu++) {
		oiommu = iommu->iommu_dev;
		ret = omap_iopgtable_store_entry(oiommu, &e);
		if (ret) {
			dev_err(dev, "omap_iopgtable_store_entry failed: %d\n",
				ret);
			break;
		}
	}

	if (ret) {
		while (i--) {
			iommu--;
			oiommu = iommu->iommu_dev;
			iopgtable_clear_entry(oiommu, da);
		}
	}

	return ret;
}