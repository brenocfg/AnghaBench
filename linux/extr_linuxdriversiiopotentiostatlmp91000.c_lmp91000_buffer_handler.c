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
struct lmp91000_data {int* buffer; } ;
struct iio_poll_func {struct iio_dev* indio_dev; } ;
struct iio_dev {int /*<<< orphan*/  trig; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  LMP91000_REG_MODECN_3LEAD ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct lmp91000_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int lmp91000_read (struct lmp91000_data*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t lmp91000_buffer_handler(int irq, void *private)
{
	struct iio_poll_func *pf = private;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct lmp91000_data *data = iio_priv(indio_dev);
	int ret, val;

	memset(data->buffer, 0, sizeof(data->buffer));

	ret = lmp91000_read(data, LMP91000_REG_MODECN_3LEAD, &val);
	if (!ret) {
		data->buffer[0] = val;
		iio_push_to_buffers_with_timestamp(indio_dev, data->buffer,
						   iio_get_time_ns(indio_dev));
	}

	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;
}