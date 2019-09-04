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
struct lidar_data {TYPE_1__* client; int /*<<< orphan*/  buffer; } ;
struct iio_poll_func {struct iio_dev* indio_dev; } ;
struct iio_dev {int /*<<< orphan*/  trig; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct lidar_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int lidar_get_measurement (struct lidar_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t lidar_trigger_handler(int irq, void *private)
{
	struct iio_poll_func *pf = private;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct lidar_data *data = iio_priv(indio_dev);
	int ret;

	ret = lidar_get_measurement(data, data->buffer);
	if (!ret) {
		iio_push_to_buffers_with_timestamp(indio_dev, data->buffer,
						   iio_get_time_ns(indio_dev));
	} else if (ret != -EINVAL) {
		dev_err(&data->client->dev, "cannot read LIDAR measurement");
	}

	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;
}