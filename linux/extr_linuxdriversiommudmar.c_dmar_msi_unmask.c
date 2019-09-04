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
struct irq_data {int /*<<< orphan*/  irq; } ;
struct intel_iommu {int reg; int /*<<< orphan*/  register_lock; } ;

/* Variables and functions */
 int dmar_msi_reg (struct intel_iommu*,int /*<<< orphan*/ ) ; 
 struct intel_iommu* irq_data_get_irq_handler_data (struct irq_data*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  readl (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int) ; 

void dmar_msi_unmask(struct irq_data *data)
{
	struct intel_iommu *iommu = irq_data_get_irq_handler_data(data);
	int reg = dmar_msi_reg(iommu, data->irq);
	unsigned long flag;

	/* unmask it */
	raw_spin_lock_irqsave(&iommu->register_lock, flag);
	writel(0, iommu->reg + reg);
	/* Read a reg to force flush the post write */
	readl(iommu->reg + reg);
	raw_spin_unlock_irqrestore(&iommu->register_lock, flag);
}