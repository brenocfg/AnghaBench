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
struct iio_trigger {int dummy; } ;
struct iio_dev {int dummy; } ;
struct ccs811_data {int drdy_trig_on; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCS811_MEAS_MODE ; 
 int CCS811_MEAS_MODE_INTERRUPT ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ccs811_data* iio_priv (struct iio_dev*) ; 
 struct iio_dev* iio_trigger_get_drvdata (struct iio_trigger*) ; 

__attribute__((used)) static int ccs811_set_trigger_state(struct iio_trigger *trig,
				    bool state)
{
	struct iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	struct ccs811_data *data = iio_priv(indio_dev);
	int ret;

	ret = i2c_smbus_read_byte_data(data->client, CCS811_MEAS_MODE);
	if (ret < 0)
		return ret;

	if (state)
		ret |= CCS811_MEAS_MODE_INTERRUPT;
	else
		ret &= ~CCS811_MEAS_MODE_INTERRUPT;

	data->drdy_trig_on = state;

	return i2c_smbus_write_byte_data(data->client, CCS811_MEAS_MODE, ret);
}