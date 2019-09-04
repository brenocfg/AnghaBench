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
struct iio_dev {int dummy; } ;
struct ds4424_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS4424_DAC_ADDR (int) ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ds4424_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ds4424_get_value(struct iio_dev *indio_dev,
			     int *val, int channel)
{
	struct ds4424_data *data = iio_priv(indio_dev);
	int ret;

	mutex_lock(&data->lock);
	ret = i2c_smbus_read_byte_data(data->client, DS4424_DAC_ADDR(channel));
	if (ret < 0)
		goto fail;

	*val = ret;

fail:
	mutex_unlock(&data->lock);
	return ret;
}