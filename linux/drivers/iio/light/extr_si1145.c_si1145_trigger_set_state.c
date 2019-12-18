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
struct si1145_data {int autonomous; int /*<<< orphan*/  lock; int /*<<< orphan*/  client; int /*<<< orphan*/  meas_rate; } ;
struct iio_trigger {int dummy; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SI1145_CMD_PSALS_AUTO ; 
 int /*<<< orphan*/  SI1145_CMD_PSALS_PAUSE ; 
 int /*<<< orphan*/  SI1145_INT_CFG_OE ; 
 int /*<<< orphan*/  SI1145_MASK_ALL_IE ; 
 int /*<<< orphan*/  SI1145_REG_INT_CFG ; 
 int /*<<< orphan*/  SI1145_REG_IRQ_ENABLE ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct si1145_data* iio_priv (struct iio_dev*) ; 
 struct iio_dev* iio_trigger_get_drvdata (struct iio_trigger*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int si1145_command (struct si1145_data*,int /*<<< orphan*/ ) ; 
 int si1145_set_meas_rate (struct si1145_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si1145_trigger_set_state(struct iio_trigger *trig, bool state)
{
	struct iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	struct si1145_data *data = iio_priv(indio_dev);
	int err = 0, ret;

	mutex_lock(&data->lock);

	if (state) {
		data->autonomous = true;
		err = i2c_smbus_write_byte_data(data->client,
				SI1145_REG_INT_CFG, SI1145_INT_CFG_OE);
		if (err < 0)
			goto disable;
		err = i2c_smbus_write_byte_data(data->client,
				SI1145_REG_IRQ_ENABLE, SI1145_MASK_ALL_IE);
		if (err < 0)
			goto disable;
		err = si1145_set_meas_rate(data, data->meas_rate);
		if (err < 0)
			goto disable;
		err = si1145_command(data, SI1145_CMD_PSALS_AUTO);
		if (err < 0)
			goto disable;
	} else {
disable:
		/* Disable as much as possible skipping errors */
		ret = si1145_command(data, SI1145_CMD_PSALS_PAUSE);
		if (ret < 0 && !err)
			err = ret;
		ret = si1145_set_meas_rate(data, 0);
		if (ret < 0 && !err)
			err = ret;
		ret = i2c_smbus_write_byte_data(data->client,
						SI1145_REG_IRQ_ENABLE, 0);
		if (ret < 0 && !err)
			err = ret;
		ret = i2c_smbus_write_byte_data(data->client,
						SI1145_REG_INT_CFG, 0);
		if (ret < 0 && !err)
			err = ret;
		data->autonomous = false;
	}

	mutex_unlock(&data->lock);
	return err;
}