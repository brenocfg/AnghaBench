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
struct srf08_data {int /*<<< orphan*/  lock; scalar_t__* buffer; } ;
struct iio_poll_func {int /*<<< orphan*/  timestamp; struct iio_dev* indio_dev; } ;
struct iio_dev {int /*<<< orphan*/  trig; } ;
typedef  scalar_t__ s16 ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 struct srf08_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ srf08_read_ranging (struct srf08_data*) ; 

__attribute__((used)) static irqreturn_t srf08_trigger_handler(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct srf08_data *data = iio_priv(indio_dev);
	s16 sensor_data;

	sensor_data = srf08_read_ranging(data);
	if (sensor_data < 0)
		goto err;

	mutex_lock(&data->lock);

	data->buffer[0] = sensor_data;
	iio_push_to_buffers_with_timestamp(indio_dev,
						data->buffer, pf->timestamp);

	mutex_unlock(&data->lock);
err:
	iio_trigger_notify_done(indio_dev->trig);
	return IRQ_HANDLED;
}