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
typedef  scalar_t__ u32 ;
struct omap_iommu_domain {int /*<<< orphan*/  dev; } ;
struct omap_iommu {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; struct iommu_domain* domain; } ;
struct iommu_domain {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  MMU_IRQENABLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__*,scalar_t__,...) ; 
 scalar_t__ iommu_report_fault (struct omap_iommu*,scalar_t__*) ; 
 int /*<<< orphan*/  iommu_write_reg (struct omap_iommu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iopgd_is_table (scalar_t__) ; 
 scalar_t__* iopgd_offset (struct omap_iommu*,scalar_t__) ; 
 scalar_t__* iopte_offset (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  report_iommu_fault (struct iommu_domain*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct omap_iommu_domain* to_omap_domain (struct iommu_domain*) ; 

__attribute__((used)) static irqreturn_t iommu_fault_handler(int irq, void *data)
{
	u32 da, errs;
	u32 *iopgd, *iopte;
	struct omap_iommu *obj = data;
	struct iommu_domain *domain = obj->domain;
	struct omap_iommu_domain *omap_domain = to_omap_domain(domain);

	if (!omap_domain->dev)
		return IRQ_NONE;

	errs = iommu_report_fault(obj, &da);
	if (errs == 0)
		return IRQ_HANDLED;

	/* Fault callback or TLB/PTE Dynamic loading */
	if (!report_iommu_fault(domain, obj->dev, da, 0))
		return IRQ_HANDLED;

	iommu_write_reg(obj, 0, MMU_IRQENABLE);

	iopgd = iopgd_offset(obj, da);

	if (!iopgd_is_table(*iopgd)) {
		dev_err(obj->dev, "%s: errs:0x%08x da:0x%08x pgd:0x%p *pgd:px%08x\n",
			obj->name, errs, da, iopgd, *iopgd);
		return IRQ_NONE;
	}

	iopte = iopte_offset(iopgd, da);

	dev_err(obj->dev, "%s: errs:0x%08x da:0x%08x pgd:0x%p *pgd:0x%08x pte:0x%p *pte:0x%08x\n",
		obj->name, errs, da, iopgd, *iopgd, iopte, *iopte);

	return IRQ_NONE;
}