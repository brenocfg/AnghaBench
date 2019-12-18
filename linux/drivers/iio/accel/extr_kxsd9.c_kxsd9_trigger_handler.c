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
struct kxsd9_state {int /*<<< orphan*/  dev; int /*<<< orphan*/  map; } ;
struct iio_poll_func {struct iio_dev* indio_dev; } ;
struct iio_dev {int /*<<< orphan*/  trig; } ;
typedef  int irqreturn_t ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int IRQ_HANDLED ; 
 int /*<<< orphan*/  KXSD9_REG_X ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct kxsd9_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static irqreturn_t kxsd9_trigger_handler(int irq, void *p)
{
	const struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct kxsd9_state *st = iio_priv(indio_dev);
	int ret;
	/* 4 * 16bit values AND timestamp */
	__be16 hw_values[8];

	ret = regmap_bulk_read(st->map,
			       KXSD9_REG_X,
			       &hw_values,
			       8);
	if (ret) {
		dev_err(st->dev,
			"error reading data\n");
		return ret;
	}

	iio_push_to_buffers_with_timestamp(indio_dev,
					   hw_values,
					   iio_get_time_ns(indio_dev));
	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;
}