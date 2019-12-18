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
struct ltc3589 {int /*<<< orphan*/  regmap; int /*<<< orphan*/ * regulators; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  LTC3589_CLIRQ ; 
 int /*<<< orphan*/  LTC3589_IRQSTAT ; 
 unsigned int LTC3589_IRQSTAT_THERMAL_WARN ; 
 unsigned int LTC3589_IRQSTAT_UNDERVOLT_WARN ; 
 unsigned int LTC3589_NUM_REGULATORS ; 
 unsigned int REGULATOR_EVENT_OVER_TEMP ; 
 unsigned int REGULATOR_EVENT_UNDER_VOLTAGE ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_notifier_call_chain (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ltc3589_isr(int irq, void *dev_id)
{
	struct ltc3589 *ltc3589 = dev_id;
	unsigned int i, irqstat, event;

	regmap_read(ltc3589->regmap, LTC3589_IRQSTAT, &irqstat);

	if (irqstat & LTC3589_IRQSTAT_THERMAL_WARN) {
		event = REGULATOR_EVENT_OVER_TEMP;
		for (i = 0; i < LTC3589_NUM_REGULATORS; i++) {
		        regulator_lock(ltc3589->regulators[i]);
			regulator_notifier_call_chain(ltc3589->regulators[i],
						      event, NULL);
		        regulator_unlock(ltc3589->regulators[i]);
		}
	}

	if (irqstat & LTC3589_IRQSTAT_UNDERVOLT_WARN) {
		event = REGULATOR_EVENT_UNDER_VOLTAGE;
		for (i = 0; i < LTC3589_NUM_REGULATORS; i++) {
		        regulator_lock(ltc3589->regulators[i]);
			regulator_notifier_call_chain(ltc3589->regulators[i],
						      event, NULL);
		        regulator_unlock(ltc3589->regulators[i]);
		}
	}

	/* Clear warning condition */
	regmap_write(ltc3589->regmap, LTC3589_CLIRQ, 0);

	return IRQ_HANDLED;
}