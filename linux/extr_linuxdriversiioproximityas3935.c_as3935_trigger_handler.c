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
struct as3935_state {int* buffer; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  AS3935_DATA ; 
 int AS3935_DATA_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int as3935_read (struct as3935_state*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct as3935_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t as3935_trigger_handler(int irq, void *private)
{
	struct iio_poll_func *pf = private;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct as3935_state *st = iio_priv(indio_dev);
	int val, ret;

	ret = as3935_read(st, AS3935_DATA, &val);
	if (ret)
		goto err_read;

	st->buffer[0] = val & AS3935_DATA_MASK;
	iio_push_to_buffers_with_timestamp(indio_dev, &st->buffer,
					   iio_get_time_ns(indio_dev));
err_read:
	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;
}