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
struct da9052 {int /*<<< orphan*/  auxadc_lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  done; } ;

/* Variables and functions */
 unsigned char DA9052_ADC_MAN_MAN_CONV ; 
 int /*<<< orphan*/  DA9052_ADC_MAN_REG ; 
 int /*<<< orphan*/  DA9052_ADC_RES_H_REG ; 
 int DA9052_ADC_RES_LSB ; 
 int /*<<< orphan*/  DA9052_ADC_RES_L_REG ; 
 unsigned char DA9052_ADC_VBBAT ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 unsigned char* chan_mux ; 
 int da9052_reg_read (struct da9052*,int /*<<< orphan*/ ) ; 
 int da9052_reg_write (struct da9052*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int da9052_adc_manual_read(struct da9052 *da9052, unsigned char channel)
{
	int ret;
	unsigned short calc_data;
	unsigned short data;
	unsigned char mux_sel;

	if (channel > DA9052_ADC_VBBAT)
		return -EINVAL;

	mutex_lock(&da9052->auxadc_lock);

	reinit_completion(&da9052->done);

	/* Channel gets activated on enabling the Conversion bit */
	mux_sel = chan_mux[channel] | DA9052_ADC_MAN_MAN_CONV;

	ret = da9052_reg_write(da9052, DA9052_ADC_MAN_REG, mux_sel);
	if (ret < 0)
		goto err;

	/* Wait for an interrupt */
	if (!wait_for_completion_timeout(&da9052->done,
					 msecs_to_jiffies(500))) {
		dev_err(da9052->dev,
			"timeout waiting for ADC conversion interrupt\n");
		ret = -ETIMEDOUT;
		goto err;
	}

	ret = da9052_reg_read(da9052, DA9052_ADC_RES_H_REG);
	if (ret < 0)
		goto err;

	calc_data = (unsigned short)ret;
	data = calc_data << 2;

	ret = da9052_reg_read(da9052, DA9052_ADC_RES_L_REG);
	if (ret < 0)
		goto err;

	calc_data = (unsigned short)(ret & DA9052_ADC_RES_LSB);
	data |= calc_data;

	ret = data;

err:
	mutex_unlock(&da9052->auxadc_lock);
	return ret;
}