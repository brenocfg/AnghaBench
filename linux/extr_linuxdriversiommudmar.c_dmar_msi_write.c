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
struct msi_msg {int /*<<< orphan*/  address_hi; int /*<<< orphan*/  address_lo; int /*<<< orphan*/  data; } ;
struct intel_iommu {int reg; int /*<<< orphan*/  register_lock; } ;

/* Variables and functions */
 int dmar_msi_reg (struct intel_iommu*,int) ; 
 struct intel_iommu* irq_get_handler_data (int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int) ; 

void dmar_msi_write(int irq, struct msi_msg *msg)
{
	struct intel_iommu *iommu = irq_get_handler_data(irq);
	int reg = dmar_msi_reg(iommu, irq);
	unsigned long flag;

	raw_spin_lock_irqsave(&iommu->register_lock, flag);
	writel(msg->data, iommu->reg + reg + 4);
	writel(msg->address_lo, iommu->reg + reg + 8);
	writel(msg->address_hi, iommu->reg + reg + 12);
	raw_spin_unlock_irqrestore(&iommu->register_lock, flag);
}