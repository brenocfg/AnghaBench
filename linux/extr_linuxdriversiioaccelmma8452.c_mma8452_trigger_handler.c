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
typedef  int /*<<< orphan*/  u8 ;
struct mma8452_data {int dummy; } ;
struct iio_poll_func {struct iio_dev* indio_dev; } ;
struct iio_dev {int /*<<< orphan*/  trig; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct mma8452_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int mma8452_read (struct mma8452_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mma8452_trigger_handler(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct mma8452_data *data = iio_priv(indio_dev);
	u8 buffer[16]; /* 3 16-bit channels + padding + ts */
	int ret;

	ret = mma8452_read(data, (__be16 *)buffer);
	if (ret < 0)
		goto done;

	iio_push_to_buffers_with_timestamp(indio_dev, buffer,
					   iio_get_time_ns(indio_dev));

done:
	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;
}