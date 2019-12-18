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
struct da9210 {int /*<<< orphan*/  regmap; int /*<<< orphan*/  rdev; } ;
typedef  int irqreturn_t ;

/* Variables and functions */
 unsigned int DA9210_E_NPWRGOOD ; 
 unsigned int DA9210_E_OVCURR ; 
 unsigned int DA9210_E_TEMP_CRIT ; 
 unsigned int DA9210_E_TEMP_WARN ; 
 unsigned int DA9210_E_VMAX ; 
 int /*<<< orphan*/  DA9210_REG_EVENT_B ; 
 int IRQ_HANDLED ; 
 int IRQ_NONE ; 
 int /*<<< orphan*/  REGULATOR_EVENT_OVER_CURRENT ; 
 int /*<<< orphan*/  REGULATOR_EVENT_OVER_TEMP ; 
 int /*<<< orphan*/  REGULATOR_EVENT_REGULATION_OUT ; 
 int /*<<< orphan*/  REGULATOR_EVENT_UNDER_VOLTAGE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  regmap_get_device (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  regulator_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_notifier_call_chain (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t da9210_irq_handler(int irq, void *data)
{
	struct da9210 *chip = data;
	unsigned int val, handled = 0;
	int error, ret = IRQ_NONE;

	error = regmap_read(chip->regmap, DA9210_REG_EVENT_B, &val);
	if (error < 0)
		goto error_i2c;

	regulator_lock(chip->rdev);

	if (val & DA9210_E_OVCURR) {
		regulator_notifier_call_chain(chip->rdev,
					      REGULATOR_EVENT_OVER_CURRENT,
					      NULL);
		handled |= DA9210_E_OVCURR;
	}
	if (val & DA9210_E_NPWRGOOD) {
		regulator_notifier_call_chain(chip->rdev,
					      REGULATOR_EVENT_UNDER_VOLTAGE,
					      NULL);
		handled |= DA9210_E_NPWRGOOD;
	}
	if (val & (DA9210_E_TEMP_WARN | DA9210_E_TEMP_CRIT)) {
		regulator_notifier_call_chain(chip->rdev,
					      REGULATOR_EVENT_OVER_TEMP, NULL);
		handled |= val & (DA9210_E_TEMP_WARN | DA9210_E_TEMP_CRIT);
	}
	if (val & DA9210_E_VMAX) {
		regulator_notifier_call_chain(chip->rdev,
					      REGULATOR_EVENT_REGULATION_OUT,
					      NULL);
		handled |= DA9210_E_VMAX;
	}

	regulator_unlock(chip->rdev);

	if (handled) {
		/* Clear handled events */
		error = regmap_write(chip->regmap, DA9210_REG_EVENT_B, handled);
		if (error < 0)
			goto error_i2c;

		ret = IRQ_HANDLED;
	}

	return ret;

error_i2c:
	dev_err(regmap_get_device(chip->regmap), "I2C error : %d\n", error);
	return ret;
}