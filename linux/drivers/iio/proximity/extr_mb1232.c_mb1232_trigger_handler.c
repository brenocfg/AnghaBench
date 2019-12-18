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
struct mb1232_data {int dummy; } ;
struct iio_poll_func {int /*<<< orphan*/  timestamp; struct iio_dev* indio_dev; } ;
struct iio_dev {int /*<<< orphan*/  trig; } ;
typedef  scalar_t__ s16 ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 struct mb1232_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 scalar_t__ mb1232_read_distance (struct mb1232_data*) ; 

__attribute__((used)) static irqreturn_t mb1232_trigger_handler(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct mb1232_data *data = iio_priv(indio_dev);
	/*
	 * triggered buffer
	 * 16-bit channel + 48-bit padding + 64-bit timestamp
	 */
	s16 buffer[8] = { 0 };

	buffer[0] = mb1232_read_distance(data);
	if (buffer[0] < 0)
		goto err;

	iio_push_to_buffers_with_timestamp(indio_dev, buffer, pf->timestamp);

err:
	iio_trigger_notify_done(indio_dev->trig);
	return IRQ_HANDLED;
}