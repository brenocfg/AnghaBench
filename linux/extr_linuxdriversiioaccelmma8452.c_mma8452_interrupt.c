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
struct mma8452_data {TYPE_1__* chip_info; int /*<<< orphan*/  client; } ;
struct iio_dev {int /*<<< orphan*/  trig; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  int irqreturn_t ;
struct TYPE_2__ {int enabled_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  IIO_ACCEL ; 
 int /*<<< orphan*/  IIO_EV_DIR_FALLING ; 
 int /*<<< orphan*/  IIO_EV_TYPE_MAG ; 
 int /*<<< orphan*/  IIO_MOD_EVENT_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IIO_MOD_X_AND_Y_AND_Z ; 
 int IRQ_HANDLED ; 
 int IRQ_NONE ; 
 int MMA8452_INT_DRDY ; 
 int MMA8452_INT_FF_MT ; 
 int /*<<< orphan*/  MMA8452_INT_SRC ; 
 int MMA8452_INT_TRANS ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct mma8452_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_event (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_poll_chained (int /*<<< orphan*/ ) ; 
 scalar_t__ mma8452_freefall_mode_enabled (struct mma8452_data*) ; 
 int /*<<< orphan*/  mma8452_transient_interrupt (struct iio_dev*) ; 

__attribute__((used)) static irqreturn_t mma8452_interrupt(int irq, void *p)
{
	struct iio_dev *indio_dev = p;
	struct mma8452_data *data = iio_priv(indio_dev);
	int ret = IRQ_NONE;
	int src;

	src = i2c_smbus_read_byte_data(data->client, MMA8452_INT_SRC);
	if (src < 0)
		return IRQ_NONE;

	if (!(src & (data->chip_info->enabled_events | MMA8452_INT_DRDY)))
		return IRQ_NONE;

	if (src & MMA8452_INT_DRDY) {
		iio_trigger_poll_chained(indio_dev->trig);
		ret = IRQ_HANDLED;
	}

	if (src & MMA8452_INT_FF_MT) {
		if (mma8452_freefall_mode_enabled(data)) {
			s64 ts = iio_get_time_ns(indio_dev);

			iio_push_event(indio_dev,
				       IIO_MOD_EVENT_CODE(IIO_ACCEL, 0,
							  IIO_MOD_X_AND_Y_AND_Z,
							  IIO_EV_TYPE_MAG,
							  IIO_EV_DIR_FALLING),
					ts);
		}
		ret = IRQ_HANDLED;
	}

	if (src & MMA8452_INT_TRANS) {
		mma8452_transient_interrupt(indio_dev);
		ret = IRQ_HANDLED;
	}

	return ret;
}