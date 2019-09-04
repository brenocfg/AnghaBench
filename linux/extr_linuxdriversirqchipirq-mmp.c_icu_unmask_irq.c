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
typedef  int u32 ;
struct irq_domain {scalar_t__ host_data; } ;
struct irq_data {int irq; struct irq_domain* domain; } ;
struct icu_chip_data {int virq_base; int conf_mask; int conf_enable; scalar_t__ reg_mask; } ;

/* Variables and functions */
 struct icu_chip_data* icu_data ; 
 scalar_t__ mmp_icu_base ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void icu_unmask_irq(struct irq_data *d)
{
	struct irq_domain *domain = d->domain;
	struct icu_chip_data *data = (struct icu_chip_data *)domain->host_data;
	int hwirq;
	u32 r;

	hwirq = d->irq - data->virq_base;
	if (data == &icu_data[0]) {
		r = readl_relaxed(mmp_icu_base + (hwirq << 2));
		r &= ~data->conf_mask;
		r |= data->conf_enable;
		writel_relaxed(r, mmp_icu_base + (hwirq << 2));
	} else {
		r = readl_relaxed(data->reg_mask) & ~(1 << hwirq);
		writel_relaxed(r, data->reg_mask);
	}
}