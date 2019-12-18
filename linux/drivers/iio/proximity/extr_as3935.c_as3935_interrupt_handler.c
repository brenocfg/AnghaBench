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
struct as3935_state {int /*<<< orphan*/  work; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 struct as3935_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t as3935_interrupt_handler(int irq, void *private)
{
	struct iio_dev *indio_dev = private;
	struct as3935_state *st = iio_priv(indio_dev);

	/*
	 * Delay work for >2 milliseconds after an interrupt to allow
	 * estimated distance to recalculated.
	 */

	schedule_delayed_work(&st->work, msecs_to_jiffies(3));

	return IRQ_HANDLED;
}