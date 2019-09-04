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
typedef  int /*<<< orphan*/  u8 ;
struct rpr0521_data {TYPE_1__* client; int /*<<< orphan*/  regmap; scalar_t__ irq_timestamp; } ;
struct iio_poll_func {scalar_t__ timestamp; struct iio_dev* indio_dev; } ;
struct iio_dev {int /*<<< orphan*/  trig; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  RPR0521_REG_PXS_DATA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ iio_get_time_ns (struct iio_dev*) ; 
 struct rpr0521_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 scalar_t__ iio_trigger_using_own (struct iio_dev*) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static irqreturn_t rpr0521_trigger_consumer_handler(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct rpr0521_data *data = iio_priv(indio_dev);
	int err;

	u8 buffer[16]; /* 3 16-bit channels + padding + ts */

	/* Use irq timestamp when reasonable. */
	if (iio_trigger_using_own(indio_dev) && data->irq_timestamp) {
		pf->timestamp = data->irq_timestamp;
		data->irq_timestamp = 0;
	}
	/* Other chained trigger polls get timestamp only here. */
	if (!pf->timestamp)
		pf->timestamp = iio_get_time_ns(indio_dev);

	err = regmap_bulk_read(data->regmap, RPR0521_REG_PXS_DATA,
		&buffer,
		(3 * 2) + 1);	/* 3 * 16-bit + (discarded) int clear reg. */
	if (!err)
		iio_push_to_buffers_with_timestamp(indio_dev,
						   buffer, pf->timestamp);
	else
		dev_err(&data->client->dev,
			"Trigger consumer can't read from sensor.\n");
	pf->timestamp = 0;

	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;
}