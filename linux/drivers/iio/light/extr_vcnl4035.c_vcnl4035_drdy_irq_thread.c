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
struct vcnl4035_data {int /*<<< orphan*/  drdy_trigger0; } ;
struct iio_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IIO_EV_DIR_EITHER ; 
 int /*<<< orphan*/  IIO_EV_TYPE_THRESH ; 
 int /*<<< orphan*/  IIO_LIGHT ; 
 int /*<<< orphan*/  IIO_UNMOD_EVENT_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct vcnl4035_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_event (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_poll_chained (int /*<<< orphan*/ ) ; 
 scalar_t__ vcnl4035_is_triggered (struct vcnl4035_data*) ; 

__attribute__((used)) static irqreturn_t vcnl4035_drdy_irq_thread(int irq, void *private)
{
	struct iio_dev *indio_dev = private;
	struct vcnl4035_data *data = iio_priv(indio_dev);

	if (vcnl4035_is_triggered(data)) {
		iio_push_event(indio_dev, IIO_UNMOD_EVENT_CODE(IIO_LIGHT,
							0,
							IIO_EV_TYPE_THRESH,
							IIO_EV_DIR_EITHER),
				iio_get_time_ns(indio_dev));
		iio_trigger_poll_chained(data->drdy_trigger0);
		return IRQ_HANDLED;
	}

	return IRQ_NONE;
}