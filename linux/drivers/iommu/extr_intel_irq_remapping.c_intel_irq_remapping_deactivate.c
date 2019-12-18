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
struct irte {int dummy; } ;
struct irq_domain {int dummy; } ;
struct irq_data {struct intel_ir_data* chip_data; } ;
struct intel_ir_data {int /*<<< orphan*/  irq_2_iommu; } ;
typedef  int /*<<< orphan*/  entry ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct irte*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  modify_irte (int /*<<< orphan*/ *,struct irte*) ; 

__attribute__((used)) static void intel_irq_remapping_deactivate(struct irq_domain *domain,
					   struct irq_data *irq_data)
{
	struct intel_ir_data *data = irq_data->chip_data;
	struct irte entry;

	memset(&entry, 0, sizeof(entry));
	modify_irte(&data->irq_2_iommu, &entry);
}