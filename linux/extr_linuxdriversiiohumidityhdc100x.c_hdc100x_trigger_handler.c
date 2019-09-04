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
typedef  int /*<<< orphan*/  u8 ;
struct iio_poll_func {struct iio_dev* indio_dev; } ;
struct iio_dev {int /*<<< orphan*/  trig; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct hdc100x_data {int* adc_int_us; int /*<<< orphan*/  lock; struct i2c_client* client; } ;
typedef  int /*<<< orphan*/  s16 ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  HDC100X_REG_TEMP ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_master_recv (struct i2c_client*,int /*<<< orphan*/ *,int) ; 
 int i2c_smbus_write_byte (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct hdc100x_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static irqreturn_t hdc100x_trigger_handler(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct hdc100x_data *data = iio_priv(indio_dev);
	struct i2c_client *client = data->client;
	int delay = data->adc_int_us[0] + data->adc_int_us[1];
	int ret;
	s16 buf[8];  /* 2x s16 + padding + 8 byte timestamp */

	/* dual read starts at temp register */
	mutex_lock(&data->lock);
	ret = i2c_smbus_write_byte(client, HDC100X_REG_TEMP);
	if (ret < 0) {
		dev_err(&client->dev, "cannot start measurement\n");
		goto err;
	}
	usleep_range(delay, delay + 1000);

	ret = i2c_master_recv(client, (u8 *)buf, 4);
	if (ret < 0) {
		dev_err(&client->dev, "cannot read sensor data\n");
		goto err;
	}

	iio_push_to_buffers_with_timestamp(indio_dev, buf,
					   iio_get_time_ns(indio_dev));
err:
	mutex_unlock(&data->lock);
	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;
}