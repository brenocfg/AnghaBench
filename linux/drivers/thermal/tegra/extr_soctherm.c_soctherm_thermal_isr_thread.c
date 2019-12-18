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
struct thermal_zone_device {int dummy; } ;
struct tegra_soctherm {scalar_t__ regs; struct thermal_zone_device** thermctl_tzs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 size_t TEGRA124_SOCTHERM_SENSOR_CPU ; 
 size_t TEGRA124_SOCTHERM_SENSOR_GPU ; 
 size_t TEGRA124_SOCTHERM_SENSOR_MEM ; 
 size_t TEGRA124_SOCTHERM_SENSOR_PLLX ; 
 int /*<<< orphan*/  THERMAL_EVENT_UNSPECIFIED ; 
 scalar_t__ THERMCTL_INTR_STATUS ; 
 int TH_INTR_CD0_MASK ; 
 int TH_INTR_CU0_MASK ; 
 int TH_INTR_GD0_MASK ; 
 int TH_INTR_GU0_MASK ; 
 int TH_INTR_IGNORE_MASK ; 
 int TH_INTR_MD0_MASK ; 
 int TH_INTR_MU0_MASK ; 
 int TH_INTR_PD0_MASK ; 
 int TH_INTR_PU0_MASK ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  thermal_zone_device_update (struct thermal_zone_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t soctherm_thermal_isr_thread(int irq, void *dev_id)
{
	struct tegra_soctherm *ts = dev_id;
	struct thermal_zone_device *tz;
	u32 st, ex = 0, cp = 0, gp = 0, pl = 0, me = 0;

	st = readl(ts->regs + THERMCTL_INTR_STATUS);

	/* deliberately clear expected interrupts handled in SW */
	cp |= st & TH_INTR_CD0_MASK;
	cp |= st & TH_INTR_CU0_MASK;

	gp |= st & TH_INTR_GD0_MASK;
	gp |= st & TH_INTR_GU0_MASK;

	pl |= st & TH_INTR_PD0_MASK;
	pl |= st & TH_INTR_PU0_MASK;

	me |= st & TH_INTR_MD0_MASK;
	me |= st & TH_INTR_MU0_MASK;

	ex |= cp | gp | pl | me;
	if (ex) {
		writel(ex, ts->regs + THERMCTL_INTR_STATUS);
		st &= ~ex;

		if (cp) {
			tz = ts->thermctl_tzs[TEGRA124_SOCTHERM_SENSOR_CPU];
			thermal_zone_device_update(tz,
						   THERMAL_EVENT_UNSPECIFIED);
		}

		if (gp) {
			tz = ts->thermctl_tzs[TEGRA124_SOCTHERM_SENSOR_GPU];
			thermal_zone_device_update(tz,
						   THERMAL_EVENT_UNSPECIFIED);
		}

		if (pl) {
			tz = ts->thermctl_tzs[TEGRA124_SOCTHERM_SENSOR_PLLX];
			thermal_zone_device_update(tz,
						   THERMAL_EVENT_UNSPECIFIED);
		}

		if (me) {
			tz = ts->thermctl_tzs[TEGRA124_SOCTHERM_SENSOR_MEM];
			thermal_zone_device_update(tz,
						   THERMAL_EVENT_UNSPECIFIED);
		}
	}

	/* deliberately ignore expected interrupts NOT handled in SW */
	ex |= TH_INTR_IGNORE_MASK;
	st &= ~ex;

	if (st) {
		/* Whine about any other unexpected INTR bits still set */
		pr_err("soctherm: Ignored unexpected INTRs 0x%08x\n", st);
		writel(st, ts->regs + THERMCTL_INTR_STATUS);
	}

	return IRQ_HANDLED;
}