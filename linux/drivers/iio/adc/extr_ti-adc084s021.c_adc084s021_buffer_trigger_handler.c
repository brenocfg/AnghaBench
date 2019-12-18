#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iio_poll_func {struct iio_dev* indio_dev; } ;
struct iio_dev {int /*<<< orphan*/  trig; } ;
struct adc084s021 {int /*<<< orphan*/  lock; TYPE_1__* spi; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ adc084s021_adc_conversion (struct adc084s021*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct adc084s021* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t adc084s021_buffer_trigger_handler(int irq, void *pollfunc)
{
	struct iio_poll_func *pf = pollfunc;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct adc084s021 *adc = iio_priv(indio_dev);
	__be16 data[8] = {0}; /* 4 * 16-bit words of data + 8 bytes timestamp */

	mutex_lock(&adc->lock);

	if (adc084s021_adc_conversion(adc, &data) < 0)
		dev_err(&adc->spi->dev, "Failed to read data\n");

	iio_push_to_buffers_with_timestamp(indio_dev, data,
					   iio_get_time_ns(indio_dev));
	mutex_unlock(&adc->lock);
	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;
}