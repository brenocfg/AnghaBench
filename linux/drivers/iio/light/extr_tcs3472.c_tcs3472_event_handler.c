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
struct tcs3472_data {int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IIO_EV_DIR_EITHER ; 
 int /*<<< orphan*/  IIO_EV_TYPE_THRESH ; 
 int /*<<< orphan*/  IIO_INTENSITY ; 
 int /*<<< orphan*/  IIO_UNMOD_EVENT_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  TCS3472_INTR_CLEAR ; 
 int /*<<< orphan*/  TCS3472_STATUS ; 
 int TCS3472_STATUS_AINT ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct tcs3472_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_event (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t tcs3472_event_handler(int irq, void *priv)
{
	struct iio_dev *indio_dev = priv;
	struct tcs3472_data *data = iio_priv(indio_dev);
	int ret;

	ret = i2c_smbus_read_byte_data(data->client, TCS3472_STATUS);
	if (ret >= 0 && (ret & TCS3472_STATUS_AINT)) {
		iio_push_event(indio_dev, IIO_UNMOD_EVENT_CODE(IIO_INTENSITY, 0,
						IIO_EV_TYPE_THRESH,
						IIO_EV_DIR_EITHER),
				iio_get_time_ns(indio_dev));

		i2c_smbus_read_byte_data(data->client, TCS3472_INTR_CLEAR);
	}

	return IRQ_HANDLED;
}