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
typedef  int /*<<< orphan*/  u32 ;
struct smsm_entry {scalar_t__ subscription; int /*<<< orphan*/  irq_enabled; struct qcom_smsm* smsm; } ;
struct qcom_smsm {scalar_t__ local_host; } ;
struct irq_data {int dummy; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 struct smsm_entry* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void smsm_unmask_irq(struct irq_data *irqd)
{
	struct smsm_entry *entry = irq_data_get_irq_chip_data(irqd);
	irq_hw_number_t irq = irqd_to_hwirq(irqd);
	struct qcom_smsm *smsm = entry->smsm;
	u32 val;

	set_bit(irq, entry->irq_enabled);

	if (entry->subscription) {
		val = readl(entry->subscription + smsm->local_host);
		val |= BIT(irq);
		writel(val, entry->subscription + smsm->local_host);
	}
}