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
struct kxcjk1013_data {scalar_t__ ev_enable_state; int /*<<< orphan*/  motion_trig; scalar_t__ motion_trigger_on; int /*<<< orphan*/  dready_trig; scalar_t__ dready_trigger_on; int /*<<< orphan*/  timestamp; } ;
struct iio_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct kxcjk1013_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_poll (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t kxcjk1013_data_rdy_trig_poll(int irq, void *private)
{
	struct iio_dev *indio_dev = private;
	struct kxcjk1013_data *data = iio_priv(indio_dev);

	data->timestamp = iio_get_time_ns(indio_dev);

	if (data->dready_trigger_on)
		iio_trigger_poll(data->dready_trig);
	else if (data->motion_trigger_on)
		iio_trigger_poll(data->motion_trig);

	if (data->ev_enable_state)
		return IRQ_WAKE_THREAD;
	else
		return IRQ_HANDLED;
}