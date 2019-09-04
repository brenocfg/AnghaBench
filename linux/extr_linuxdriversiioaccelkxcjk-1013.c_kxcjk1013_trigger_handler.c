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
struct kxcjk1013_data {int /*<<< orphan*/  timestamp; scalar_t__ buffer; int /*<<< orphan*/  mutex; int /*<<< orphan*/  client; } ;
struct iio_poll_func {struct iio_dev* indio_dev; } ;
struct iio_dev {int /*<<< orphan*/  trig; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int AXIS_MAX ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  KXCJK1013_REG_XOUT_L ; 
 int i2c_smbus_read_i2c_block_data_or_emulated (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct kxcjk1013_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t kxcjk1013_trigger_handler(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct kxcjk1013_data *data = iio_priv(indio_dev);
	int ret;

	mutex_lock(&data->mutex);
	ret = i2c_smbus_read_i2c_block_data_or_emulated(data->client,
							KXCJK1013_REG_XOUT_L,
							AXIS_MAX * 2,
							(u8 *)data->buffer);
	mutex_unlock(&data->mutex);
	if (ret < 0)
		goto err;

	iio_push_to_buffers_with_timestamp(indio_dev, data->buffer,
					   data->timestamp);
err:
	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;
}