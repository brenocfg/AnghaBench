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
struct iio_poll_func {struct iio_dev* indio_dev; } ;
struct iio_dev {int /*<<< orphan*/  trig; } ;
struct hmc5843_data {int /*<<< orphan*/  buffer; int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  HMC5843_DATA_OUT_MSB_REGS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int hmc5843_wait_measurement (struct hmc5843_data*) ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct hmc5843_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t hmc5843_trigger_handler(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct hmc5843_data *data = iio_priv(indio_dev);
	int ret;

	mutex_lock(&data->lock);
	ret = hmc5843_wait_measurement(data);
	if (ret < 0) {
		mutex_unlock(&data->lock);
		goto done;
	}

	ret = regmap_bulk_read(data->regmap, HMC5843_DATA_OUT_MSB_REGS,
			       data->buffer, 3 * sizeof(__be16));

	mutex_unlock(&data->lock);
	if (ret < 0)
		goto done;

	iio_push_to_buffers_with_timestamp(indio_dev, data->buffer,
					   iio_get_time_ns(indio_dev));

done:
	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;
}