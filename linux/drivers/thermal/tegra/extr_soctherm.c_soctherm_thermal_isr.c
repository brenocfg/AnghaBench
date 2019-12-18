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
struct tegra_soctherm {scalar_t__ regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 scalar_t__ THERMCTL_INTR_DISABLE ; 
 scalar_t__ THERMCTL_INTR_STATUS ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t soctherm_thermal_isr(int irq, void *dev_id)
{
	struct tegra_soctherm *ts = dev_id;
	u32 r;

	/* Case for no lock:
	 * Although interrupts are enabled in set_trips, there is still no need
	 * to lock here because the interrupts are disabled before programming
	 * new trip points. Hence there cant be a interrupt on the same sensor.
	 * An interrupt can however occur on a sensor while trips are being
	 * programmed on a different one. This beign a LEVEL interrupt won't
	 * cause a new interrupt but this is taken care of by the re-reading of
	 * the STATUS register in the thread function.
	 */
	r = readl(ts->regs + THERMCTL_INTR_STATUS);
	writel(r, ts->regs + THERMCTL_INTR_DISABLE);

	return IRQ_WAKE_THREAD;
}