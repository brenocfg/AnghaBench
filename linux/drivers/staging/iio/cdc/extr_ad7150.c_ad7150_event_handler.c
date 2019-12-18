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
typedef  int u8 ;
struct iio_dev {int dummy; } ;
struct ad7150_chip_info {int old_state; int /*<<< orphan*/  client; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  AD7150_STATUS ; 
 int AD7150_STATUS_OUT1 ; 
 int AD7150_STATUS_OUT2 ; 
 int /*<<< orphan*/  IIO_CAPACITANCE ; 
 int /*<<< orphan*/  IIO_EV_DIR_FALLING ; 
 int /*<<< orphan*/  IIO_EV_DIR_RISING ; 
 int /*<<< orphan*/  IIO_EV_TYPE_THRESH ; 
 int /*<<< orphan*/  IIO_UNMOD_EVENT_CODE (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct ad7150_chip_info* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_event (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ad7150_event_handler(int irq, void *private)
{
	struct iio_dev *indio_dev = private;
	struct ad7150_chip_info *chip = iio_priv(indio_dev);
	u8 int_status;
	s64 timestamp = iio_get_time_ns(indio_dev);
	int ret;

	ret = i2c_smbus_read_byte_data(chip->client, AD7150_STATUS);
	if (ret < 0)
		return IRQ_HANDLED;

	int_status = ret;

	if ((int_status & AD7150_STATUS_OUT1) &&
	    !(chip->old_state & AD7150_STATUS_OUT1))
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_CAPACITANCE,
						    0,
						    IIO_EV_TYPE_THRESH,
						    IIO_EV_DIR_RISING),
				timestamp);
	else if ((!(int_status & AD7150_STATUS_OUT1)) &&
		 (chip->old_state & AD7150_STATUS_OUT1))
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_CAPACITANCE,
						    0,
						    IIO_EV_TYPE_THRESH,
						    IIO_EV_DIR_FALLING),
			       timestamp);

	if ((int_status & AD7150_STATUS_OUT2) &&
	    !(chip->old_state & AD7150_STATUS_OUT2))
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_CAPACITANCE,
						    1,
						    IIO_EV_TYPE_THRESH,
						    IIO_EV_DIR_RISING),
			       timestamp);
	else if ((!(int_status & AD7150_STATUS_OUT2)) &&
		 (chip->old_state & AD7150_STATUS_OUT2))
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_CAPACITANCE,
						    1,
						    IIO_EV_TYPE_THRESH,
						    IIO_EV_DIR_FALLING),
			       timestamp);
	/* store the status to avoid repushing same events */
	chip->old_state = int_status;

	return IRQ_HANDLED;
}