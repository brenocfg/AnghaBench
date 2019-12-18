#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* ttbr; } ;
struct TYPE_5__ {TYPE_1__ arm_v7s_cfg; } ;
struct mtk_iommu_domain {TYPE_2__ cfg; } ;
struct mtk_iommu_data {scalar_t__ base; struct mtk_iommu_domain* m4u_dom; } ;
struct iommu_domain {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_6__ {struct mtk_iommu_data* iommu_priv; } ;

/* Variables and functions */
 int ENODEV ; 
 int MMU_PT_ADDR_MASK ; 
 scalar_t__ REG_MMU_PT_BASE_ADDR ; 
 TYPE_3__* dev_iommu_fwspec_get (struct device*) ; 
 int /*<<< orphan*/  mtk_iommu_config (struct mtk_iommu_data*,struct device*,int) ; 
 struct mtk_iommu_domain* to_mtk_domain (struct iommu_domain*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mtk_iommu_attach_device(struct iommu_domain *domain,
				   struct device *dev)
{
	struct mtk_iommu_domain *dom = to_mtk_domain(domain);
	struct mtk_iommu_data *data = dev_iommu_fwspec_get(dev)->iommu_priv;

	if (!data)
		return -ENODEV;

	/* Update the pgtable base address register of the M4U HW */
	if (!data->m4u_dom) {
		data->m4u_dom = dom;
		writel(dom->cfg.arm_v7s_cfg.ttbr[0] & MMU_PT_ADDR_MASK,
		       data->base + REG_MMU_PT_BASE_ADDR);
	}

	mtk_iommu_config(data, dev, true);
	return 0;
}