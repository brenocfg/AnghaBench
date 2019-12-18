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
typedef  int u32 ;
struct tegra_soctherm {scalar_t__ regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int irq_enable; int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int OC_INTR_OC1_MASK ; 
 int OC_INTR_OC2_MASK ; 
 int OC_INTR_OC3_MASK ; 
 int OC_INTR_OC4_MASK ; 
 scalar_t__ OC_INTR_STATUS ; 
 int /*<<< orphan*/  THROTTLE_OC1 ; 
 int /*<<< orphan*/  THROTTLE_OC2 ; 
 int /*<<< orphan*/  THROTTLE_OC3 ; 
 int /*<<< orphan*/  THROTTLE_OC4 ; 
 int /*<<< orphan*/  handle_nested_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_find_mapping (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int readl (scalar_t__) ; 
 TYPE_1__ soc_irq_cdata ; 
 int /*<<< orphan*/  soctherm_handle_alarm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soctherm_oc_intr_enable (struct tegra_soctherm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t soctherm_edp_isr_thread(int irq, void *arg)
{
	struct tegra_soctherm *ts = arg;
	u32 st, ex, oc1, oc2, oc3, oc4;

	st = readl(ts->regs + OC_INTR_STATUS);

	/* deliberately clear expected interrupts handled in SW */
	oc1 = st & OC_INTR_OC1_MASK;
	oc2 = st & OC_INTR_OC2_MASK;
	oc3 = st & OC_INTR_OC3_MASK;
	oc4 = st & OC_INTR_OC4_MASK;
	ex = oc1 | oc2 | oc3 | oc4;

	pr_err("soctherm: OC ALARM 0x%08x\n", ex);
	if (ex) {
		writel(st, ts->regs + OC_INTR_STATUS);
		st &= ~ex;

		if (oc1 && !soctherm_handle_alarm(THROTTLE_OC1))
			soctherm_oc_intr_enable(ts, THROTTLE_OC1, true);

		if (oc2 && !soctherm_handle_alarm(THROTTLE_OC2))
			soctherm_oc_intr_enable(ts, THROTTLE_OC2, true);

		if (oc3 && !soctherm_handle_alarm(THROTTLE_OC3))
			soctherm_oc_intr_enable(ts, THROTTLE_OC3, true);

		if (oc4 && !soctherm_handle_alarm(THROTTLE_OC4))
			soctherm_oc_intr_enable(ts, THROTTLE_OC4, true);

		if (oc1 && soc_irq_cdata.irq_enable & BIT(0))
			handle_nested_irq(
				irq_find_mapping(soc_irq_cdata.domain, 0));

		if (oc2 && soc_irq_cdata.irq_enable & BIT(1))
			handle_nested_irq(
				irq_find_mapping(soc_irq_cdata.domain, 1));

		if (oc3 && soc_irq_cdata.irq_enable & BIT(2))
			handle_nested_irq(
				irq_find_mapping(soc_irq_cdata.domain, 2));

		if (oc4 && soc_irq_cdata.irq_enable & BIT(3))
			handle_nested_irq(
				irq_find_mapping(soc_irq_cdata.domain, 3));
	}

	if (st) {
		pr_err("soctherm: Ignored unexpected OC ALARM 0x%08x\n", st);
		writel(st, ts->regs + OC_INTR_STATUS);
	}

	return IRQ_HANDLED;
}