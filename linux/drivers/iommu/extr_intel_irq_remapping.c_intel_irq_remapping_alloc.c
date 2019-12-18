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
struct irq_domain {struct intel_iommu* host_data; } ;
struct irq_data {int hwirq; int /*<<< orphan*/ * chip; struct intel_ir_data* chip_data; } ;
struct irq_cfg {int dummy; } ;
struct irq_alloc_info {scalar_t__ type; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int sub_handle; } ;
struct intel_ir_data {TYPE_1__ irq_2_iommu; } ;
struct intel_iommu {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQ_MOVE_PCNTXT ; 
 int /*<<< orphan*/  X86_IRQ_ALLOC_CONTIGUOUS_VECTORS ; 
 scalar_t__ X86_IRQ_ALLOC_TYPE_MSI ; 
 scalar_t__ X86_IRQ_ALLOC_TYPE_MSIX ; 
 int alloc_irte (struct intel_iommu*,TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  dmar_global_lock ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_free_irq_resources (struct irq_domain*,unsigned int,int) ; 
 int /*<<< orphan*/  intel_ir_chip ; 
 int /*<<< orphan*/  intel_irq_remapping_prepare_irte (struct intel_ir_data*,struct irq_cfg*,struct irq_alloc_info*,int,int) ; 
 int irq_domain_alloc_irqs_parent (struct irq_domain*,unsigned int,unsigned int,void*) ; 
 int /*<<< orphan*/  irq_domain_free_irqs_common (struct irq_domain*,unsigned int,unsigned int) ; 
 struct irq_data* irq_domain_get_irq_data (struct irq_domain*,unsigned int) ; 
 int /*<<< orphan*/  irq_set_status_flags (unsigned int,int /*<<< orphan*/ ) ; 
 struct irq_cfg* irqd_cfg (struct irq_data*) ; 
 int /*<<< orphan*/  kfree (struct intel_ir_data*) ; 
 struct intel_ir_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int intel_irq_remapping_alloc(struct irq_domain *domain,
				     unsigned int virq, unsigned int nr_irqs,
				     void *arg)
{
	struct intel_iommu *iommu = domain->host_data;
	struct irq_alloc_info *info = arg;
	struct intel_ir_data *data, *ird;
	struct irq_data *irq_data;
	struct irq_cfg *irq_cfg;
	int i, ret, index;

	if (!info || !iommu)
		return -EINVAL;
	if (nr_irqs > 1 && info->type != X86_IRQ_ALLOC_TYPE_MSI &&
	    info->type != X86_IRQ_ALLOC_TYPE_MSIX)
		return -EINVAL;

	/*
	 * With IRQ remapping enabled, don't need contiguous CPU vectors
	 * to support multiple MSI interrupts.
	 */
	if (info->type == X86_IRQ_ALLOC_TYPE_MSI)
		info->flags &= ~X86_IRQ_ALLOC_CONTIGUOUS_VECTORS;

	ret = irq_domain_alloc_irqs_parent(domain, virq, nr_irqs, arg);
	if (ret < 0)
		return ret;

	ret = -ENOMEM;
	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		goto out_free_parent;

	down_read(&dmar_global_lock);
	index = alloc_irte(iommu, &data->irq_2_iommu, nr_irqs);
	up_read(&dmar_global_lock);
	if (index < 0) {
		pr_warn("Failed to allocate IRTE\n");
		kfree(data);
		goto out_free_parent;
	}

	for (i = 0; i < nr_irqs; i++) {
		irq_data = irq_domain_get_irq_data(domain, virq + i);
		irq_cfg = irqd_cfg(irq_data);
		if (!irq_data || !irq_cfg) {
			ret = -EINVAL;
			goto out_free_data;
		}

		if (i > 0) {
			ird = kzalloc(sizeof(*ird), GFP_KERNEL);
			if (!ird)
				goto out_free_data;
			/* Initialize the common data */
			ird->irq_2_iommu = data->irq_2_iommu;
			ird->irq_2_iommu.sub_handle = i;
		} else {
			ird = data;
		}

		irq_data->hwirq = (index << 16) + i;
		irq_data->chip_data = ird;
		irq_data->chip = &intel_ir_chip;
		intel_irq_remapping_prepare_irte(ird, irq_cfg, info, index, i);
		irq_set_status_flags(virq + i, IRQ_MOVE_PCNTXT);
	}
	return 0;

out_free_data:
	intel_free_irq_resources(domain, virq, i);
out_free_parent:
	irq_domain_free_irqs_common(domain, virq, nr_irqs);
	return ret;
}