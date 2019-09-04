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
struct mxc4005_data {int /*<<< orphan*/  buffer; } ;
struct iio_poll_func {int /*<<< orphan*/  timestamp; struct iio_dev* indio_dev; } ;
struct iio_dev {int /*<<< orphan*/  trig; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 struct mxc4005_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int mxc4005_read_xyz (struct mxc4005_data*) ; 

__attribute__((used)) static irqreturn_t mxc4005_trigger_handler(int irq, void *private)
{
	struct iio_poll_func *pf = private;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct mxc4005_data *data = iio_priv(indio_dev);
	int ret;

	ret = mxc4005_read_xyz(data);
	if (ret < 0)
		goto err;

	iio_push_to_buffers_with_timestamp(indio_dev, data->buffer,
					   pf->timestamp);

err:
	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;
}