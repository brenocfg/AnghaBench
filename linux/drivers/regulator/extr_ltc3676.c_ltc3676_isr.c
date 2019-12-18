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
struct ltc3676 {int /*<<< orphan*/  regmap; int /*<<< orphan*/ * regulators; struct device* dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  LTC3676_CLIRQ ; 
 int /*<<< orphan*/  LTC3676_IRQSTAT ; 
 unsigned int LTC3676_IRQSTAT_THERMAL_WARN ; 
 unsigned int LTC3676_IRQSTAT_UNDERVOLT_WARN ; 
 unsigned int LTC3676_NUM_REGULATORS ; 
 unsigned int REGULATOR_EVENT_OVER_TEMP ; 
 unsigned int REGULATOR_EVENT_UNDER_VOLTAGE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,unsigned int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_notifier_call_chain (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ltc3676_isr(int irq, void *dev_id)
{
	struct ltc3676 *ltc3676 = dev_id;
	struct device *dev = ltc3676->dev;
	unsigned int i, irqstat, event;

	regmap_read(ltc3676->regmap, LTC3676_IRQSTAT, &irqstat);

	dev_dbg(dev, "irq%d irqstat=0x%02x\n", irq, irqstat);
	if (irqstat & LTC3676_IRQSTAT_THERMAL_WARN) {
		dev_warn(dev, "Over-temperature Warning\n");
		event = REGULATOR_EVENT_OVER_TEMP;
		for (i = 0; i < LTC3676_NUM_REGULATORS; i++) {
			regulator_lock(ltc3676->regulators[i]);
			regulator_notifier_call_chain(ltc3676->regulators[i],
						      event, NULL);
			regulator_unlock(ltc3676->regulators[i]);
		}
	}

	if (irqstat & LTC3676_IRQSTAT_UNDERVOLT_WARN) {
		dev_info(dev, "Undervoltage Warning\n");
		event = REGULATOR_EVENT_UNDER_VOLTAGE;
		for (i = 0; i < LTC3676_NUM_REGULATORS; i++) {
			regulator_lock(ltc3676->regulators[i]);
			regulator_notifier_call_chain(ltc3676->regulators[i],
						      event, NULL);
			regulator_unlock(ltc3676->regulators[i]);
		}
	}

	/* Clear warning condition */
	regmap_write(ltc3676->regmap, LTC3676_CLIRQ, 0);

	return IRQ_HANDLED;
}