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
struct rpr0521_data {int /*<<< orphan*/  drdy_trigger0; } ;
struct iio_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 struct rpr0521_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_poll_chained (int /*<<< orphan*/ ) ; 
 scalar_t__ rpr0521_is_triggered (struct rpr0521_data*) ; 

__attribute__((used)) static irqreturn_t rpr0521_drdy_irq_thread(int irq, void *private)
{
	struct iio_dev *indio_dev = private;
	struct rpr0521_data *data = iio_priv(indio_dev);

	if (rpr0521_is_triggered(data)) {
		iio_trigger_poll_chained(data->drdy_trigger0);
		return IRQ_HANDLED;
	}

	return IRQ_NONE;
}