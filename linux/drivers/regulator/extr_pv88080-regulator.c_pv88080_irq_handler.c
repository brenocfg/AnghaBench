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
struct pv88080 {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; int /*<<< orphan*/ ** rdev; } ;
typedef  int irqreturn_t ;

/* Variables and functions */
 int IRQ_HANDLED ; 
 int IRQ_NONE ; 
 int PV88080_E_OVER_TEMP ; 
 int PV88080_E_VDD_FLT ; 
 int PV88080_MAX_REGULATORS ; 
 int /*<<< orphan*/  PV88080_REG_EVENT_A ; 
 int /*<<< orphan*/  REGULATOR_EVENT_OVER_TEMP ; 
 int /*<<< orphan*/  REGULATOR_EVENT_UNDER_VOLTAGE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regulator_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t pv88080_irq_handler(int irq, void *data)
{
	struct pv88080 *chip = data;
	int i, reg_val, err, ret = IRQ_NONE;

	err = regmap_read(chip->regmap, PV88080_REG_EVENT_A, &reg_val);
	if (err < 0)
		goto error_i2c;

	if (reg_val & PV88080_E_VDD_FLT) {
		for (i = 0; i < PV88080_MAX_REGULATORS; i++) {
			if (chip->rdev[i] != NULL) {
			        regulator_lock(chip->rdev[i]);
				regulator_notifier_call_chain(chip->rdev[i],
					REGULATOR_EVENT_UNDER_VOLTAGE,
					NULL);
			        regulator_unlock(chip->rdev[i]);
			}
		}

		err = regmap_write(chip->regmap, PV88080_REG_EVENT_A,
			PV88080_E_VDD_FLT);
		if (err < 0)
			goto error_i2c;

		ret = IRQ_HANDLED;
	}

	if (reg_val & PV88080_E_OVER_TEMP) {
		for (i = 0; i < PV88080_MAX_REGULATORS; i++) {
			if (chip->rdev[i] != NULL) {
			        regulator_lock(chip->rdev[i]);
				regulator_notifier_call_chain(chip->rdev[i],
					REGULATOR_EVENT_OVER_TEMP,
					NULL);
			        regulator_unlock(chip->rdev[i]);
			}
		}

		err = regmap_write(chip->regmap, PV88080_REG_EVENT_A,
			PV88080_E_OVER_TEMP);
		if (err < 0)
			goto error_i2c;

		ret = IRQ_HANDLED;
	}

	return ret;

error_i2c:
	dev_err(chip->dev, "I2C error : %d\n", err);
	return IRQ_NONE;
}