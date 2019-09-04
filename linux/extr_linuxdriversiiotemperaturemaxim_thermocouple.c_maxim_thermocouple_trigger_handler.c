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
struct maxim_thermocouple_data {int /*<<< orphan*/  buffer; TYPE_1__* chip; int /*<<< orphan*/  spi; } ;
struct iio_poll_func {struct iio_dev* indio_dev; } ;
struct iio_dev {int /*<<< orphan*/  trig; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  read_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct maxim_thermocouple_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int spi_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t maxim_thermocouple_trigger_handler(int irq, void *private)
{
	struct iio_poll_func *pf = private;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct maxim_thermocouple_data *data = iio_priv(indio_dev);
	int ret;

	ret = spi_read(data->spi, data->buffer, data->chip->read_size);
	if (!ret) {
		iio_push_to_buffers_with_timestamp(indio_dev, data->buffer,
						   iio_get_time_ns(indio_dev));
	}

	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;
}