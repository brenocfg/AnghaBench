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
struct iio_dev {int dummy; } ;
struct bmc150_accel_data {scalar_t__ fifo_mode; scalar_t__ ev_enable_state; TYPE_1__* triggers; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  old_timestamp; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  indio_trig; scalar_t__ enabled; } ;

/* Variables and functions */
 int BMC150_ACCEL_TRIGGERS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct bmc150_accel_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_poll (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t bmc150_accel_irq_handler(int irq, void *private)
{
	struct iio_dev *indio_dev = private;
	struct bmc150_accel_data *data = iio_priv(indio_dev);
	bool ack = false;
	int i;

	data->old_timestamp = data->timestamp;
	data->timestamp = iio_get_time_ns(indio_dev);

	for (i = 0; i < BMC150_ACCEL_TRIGGERS; i++) {
		if (data->triggers[i].enabled) {
			iio_trigger_poll(data->triggers[i].indio_trig);
			ack = true;
			break;
		}
	}

	if (data->ev_enable_state || data->fifo_mode)
		return IRQ_WAKE_THREAD;

	if (ack)
		return IRQ_HANDLED;

	return IRQ_NONE;
}