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
struct iio_dev {int dummy; } ;
struct ad7606_state {int /*<<< orphan*/  completion; int /*<<< orphan*/  trig; int /*<<< orphan*/  gpio_convst; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iio_buffer_enabled (struct iio_dev*) ; 
 struct ad7606_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_poll_chained (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ad7606_interrupt(int irq, void *dev_id)
{
	struct iio_dev *indio_dev = dev_id;
	struct ad7606_state *st = iio_priv(indio_dev);

	if (iio_buffer_enabled(indio_dev)) {
		gpiod_set_value(st->gpio_convst, 0);
		iio_trigger_poll_chained(st->trig);
	} else {
		complete(&st->completion);
	}

	return IRQ_HANDLED;
}