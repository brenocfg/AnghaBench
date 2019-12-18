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
struct fxas21002c_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  buffer; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  s16 ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int CHANNEL_SCAN_MAX ; 
 int /*<<< orphan*/  FXAS21002C_REG_OUT_X_MSB ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 struct fxas21002c_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t fxas21002c_trigger_handler(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct fxas21002c_data *data = iio_priv(indio_dev);
	int ret;

	mutex_lock(&data->lock);
	ret = regmap_bulk_read(data->regmap, FXAS21002C_REG_OUT_X_MSB,
			       data->buffer, CHANNEL_SCAN_MAX * sizeof(s16));
	if (ret < 0)
		goto out_unlock;

	iio_push_to_buffers_with_timestamp(indio_dev, data->buffer,
					   data->timestamp);

out_unlock:
	mutex_unlock(&data->lock);

	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;
}