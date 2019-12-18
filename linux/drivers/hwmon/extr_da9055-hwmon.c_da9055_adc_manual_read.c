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
struct da9055_hwmon {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  done; struct da9055* da9055; } ;
struct da9055 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DA9055_ADC_LSB_MASK ; 
 unsigned char DA9055_ADC_MAN_CONV ; 
 unsigned char DA9055_ADC_TJUNC ; 
 int /*<<< orphan*/  DA9055_REG_ADC_MAN ; 
 int /*<<< orphan*/  DA9055_REG_ADC_RES_H ; 
 int /*<<< orphan*/  DA9055_REG_ADC_RES_L ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 unsigned char* chan_mux ; 
 int da9055_reg_read (struct da9055*,int /*<<< orphan*/ ) ; 
 int da9055_reg_write (struct da9055*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9055_adc_manual_read(struct da9055_hwmon *hwmon,
					unsigned char channel)
{
	int ret;
	unsigned short calc_data;
	unsigned short data;
	unsigned char mux_sel;
	struct da9055 *da9055 = hwmon->da9055;

	if (channel > DA9055_ADC_TJUNC)
		return -EINVAL;

	mutex_lock(&hwmon->irq_lock);

	/* Selects desired MUX for manual conversion */
	mux_sel = chan_mux[channel] | DA9055_ADC_MAN_CONV;

	ret = da9055_reg_write(da9055, DA9055_REG_ADC_MAN, mux_sel);
	if (ret < 0)
		goto err;

	/* Wait for an interrupt */
	if (!wait_for_completion_timeout(&hwmon->done,
					msecs_to_jiffies(500))) {
		dev_err(da9055->dev,
			"timeout waiting for ADC conversion interrupt\n");
		ret = -ETIMEDOUT;
		goto err;
	}

	ret = da9055_reg_read(da9055, DA9055_REG_ADC_RES_H);
	if (ret < 0)
		goto err;

	calc_data = (unsigned short)ret;
	data = calc_data << 2;

	ret = da9055_reg_read(da9055, DA9055_REG_ADC_RES_L);
	if (ret < 0)
		goto err;

	calc_data = (unsigned short)(ret & DA9055_ADC_LSB_MASK);
	data |= calc_data;

	ret = data;

err:
	mutex_unlock(&hwmon->irq_lock);
	return ret;
}