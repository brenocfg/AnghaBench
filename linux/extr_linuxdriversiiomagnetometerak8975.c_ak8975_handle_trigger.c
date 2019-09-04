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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  ak8975_fill_buffer (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ak8975_handle_trigger(int irq, void *p)
{
	const struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;

	ak8975_fill_buffer(indio_dev);
	iio_trigger_notify_done(indio_dev->trig);
	return IRQ_HANDLED;
}