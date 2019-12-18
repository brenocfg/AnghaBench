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
struct iio_poll_func {int /*<<< orphan*/  timestamp; struct iio_dev* indio_dev; } ;
struct iio_dev {int /*<<< orphan*/  trig; } ;
struct bmc150_magn_data {int /*<<< orphan*/  mutex; int /*<<< orphan*/  buffer; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int bmc150_magn_read_xyz (struct bmc150_magn_data*,int /*<<< orphan*/ ) ; 
 struct bmc150_magn_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t bmc150_magn_trigger_handler(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct bmc150_magn_data *data = iio_priv(indio_dev);
	int ret;

	mutex_lock(&data->mutex);
	ret = bmc150_magn_read_xyz(data, data->buffer);
	if (ret < 0)
		goto err;

	iio_push_to_buffers_with_timestamp(indio_dev, data->buffer,
					   pf->timestamp);

err:
	mutex_unlock(&data->mutex);
	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;
}