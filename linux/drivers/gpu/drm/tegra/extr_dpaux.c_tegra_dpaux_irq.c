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
struct tegra_dpaux {int /*<<< orphan*/  complete; int /*<<< orphan*/  work; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPAUX_INTR_AUX ; 
 int DPAUX_INTR_AUX_DONE ; 
 int DPAUX_INTR_IRQ_EVENT ; 
 int DPAUX_INTR_PLUG_EVENT ; 
 int DPAUX_INTR_UNPLUG_EVENT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int tegra_dpaux_readl (struct tegra_dpaux*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_dpaux_writel (struct tegra_dpaux*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t tegra_dpaux_irq(int irq, void *data)
{
	struct tegra_dpaux *dpaux = data;
	irqreturn_t ret = IRQ_HANDLED;
	u32 value;

	/* clear interrupts */
	value = tegra_dpaux_readl(dpaux, DPAUX_INTR_AUX);
	tegra_dpaux_writel(dpaux, value, DPAUX_INTR_AUX);

	if (value & (DPAUX_INTR_PLUG_EVENT | DPAUX_INTR_UNPLUG_EVENT))
		schedule_work(&dpaux->work);

	if (value & DPAUX_INTR_IRQ_EVENT) {
		/* TODO: handle this */
	}

	if (value & DPAUX_INTR_AUX_DONE)
		complete(&dpaux->complete);

	return ret;
}