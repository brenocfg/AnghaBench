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
struct mma8452_data {int /*<<< orphan*/  client; } ;
struct iio_trigger {int dummy; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMA8452_CTRL_REG4 ; 
 int MMA8452_INT_DRDY ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mma8452_data* iio_priv (struct iio_dev*) ; 
 struct iio_dev* iio_trigger_get_drvdata (struct iio_trigger*) ; 
 int mma8452_change_config (struct mma8452_data*,int /*<<< orphan*/ ,int) ; 
 int mma8452_set_runtime_pm_state (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mma8452_data_rdy_trigger_set_state(struct iio_trigger *trig,
					      bool state)
{
	struct iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	struct mma8452_data *data = iio_priv(indio_dev);
	int reg, ret;

	ret = mma8452_set_runtime_pm_state(data->client, state);
	if (ret)
		return ret;

	reg = i2c_smbus_read_byte_data(data->client, MMA8452_CTRL_REG4);
	if (reg < 0)
		return reg;

	if (state)
		reg |= MMA8452_INT_DRDY;
	else
		reg &= ~MMA8452_INT_DRDY;

	return mma8452_change_config(data, MMA8452_CTRL_REG4, reg);
}