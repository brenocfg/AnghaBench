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
struct spi_device {int dummy; } ;
struct iio_poll_func {int /*<<< orphan*/  timestamp; struct iio_dev* indio_dev; } ;
struct iio_dev {int /*<<< orphan*/  trig; } ;
struct bma220_data {int* tx_buf; int /*<<< orphan*/  lock; int /*<<< orphan*/  buffer; struct spi_device* spi_device; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int BMA220_READ_MASK ; 
 int BMA220_REG_ACCEL_X ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  bma220_channels ; 
 struct bma220_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int spi_write_then_read (struct spi_device*,int*,int,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t bma220_trigger_handler(int irq, void *p)
{
	int ret;
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct bma220_data *data = iio_priv(indio_dev);
	struct spi_device *spi = data->spi_device;

	mutex_lock(&data->lock);
	data->tx_buf[0] = BMA220_REG_ACCEL_X | BMA220_READ_MASK;
	ret = spi_write_then_read(spi, data->tx_buf, 1, data->buffer,
				  ARRAY_SIZE(bma220_channels) - 1);
	if (ret < 0)
		goto err;

	iio_push_to_buffers_with_timestamp(indio_dev, data->buffer,
					   pf->timestamp);
err:
	mutex_unlock(&data->lock);
	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;
}