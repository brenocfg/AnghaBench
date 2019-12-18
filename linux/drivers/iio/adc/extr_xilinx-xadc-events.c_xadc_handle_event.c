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
struct iio_chan_spec {scalar_t__ type; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  IIO_EV_DIR_EITHER ; 
 int /*<<< orphan*/  IIO_EV_DIR_RISING ; 
 int /*<<< orphan*/  IIO_EV_TYPE_THRESH ; 
 scalar_t__ IIO_TEMP ; 
 int /*<<< orphan*/  IIO_UNMOD_EVENT_CODE (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_event (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iio_chan_spec* xadc_event_to_channel (struct iio_dev*,unsigned int) ; 

__attribute__((used)) static void xadc_handle_event(struct iio_dev *indio_dev, unsigned int event)
{
	const struct iio_chan_spec *chan;

	/* Temperature threshold error, we don't handle this yet */
	if (event == 0)
		return;

	chan = xadc_event_to_channel(indio_dev, event);

	if (chan->type == IIO_TEMP) {
		/*
		 * The temperature channel only supports over-temperature
		 * events.
		 */
		iio_push_event(indio_dev,
			IIO_UNMOD_EVENT_CODE(chan->type, chan->channel,
				IIO_EV_TYPE_THRESH, IIO_EV_DIR_RISING),
			iio_get_time_ns(indio_dev));
	} else {
		/*
		 * For other channels we don't know whether it is a upper or
		 * lower threshold event. Userspace will have to check the
		 * channel value if it wants to know.
		 */
		iio_push_event(indio_dev,
			IIO_UNMOD_EVENT_CODE(chan->type, chan->channel,
				IIO_EV_TYPE_THRESH, IIO_EV_DIR_EITHER),
			iio_get_time_ns(indio_dev));
	}
}