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
struct ad799x_state {int /*<<< orphan*/  client; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  AD7998_ALERT_STAT_CLEAR ; 
 int /*<<< orphan*/  AD7998_ALERT_STAT_REG ; 
 int BIT (int) ; 
 int /*<<< orphan*/  IIO_EV_DIR_FALLING ; 
 int /*<<< orphan*/  IIO_EV_DIR_RISING ; 
 int /*<<< orphan*/  IIO_EV_TYPE_THRESH ; 
 int /*<<< orphan*/  IIO_UNMOD_EVENT_CODE (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IIO_VOLTAGE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct ad799x_state* iio_priv (void*) ; 
 int /*<<< orphan*/  iio_push_event (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ad799x_event_handler(int irq, void *private)
{
	struct iio_dev *indio_dev = private;
	struct ad799x_state *st = iio_priv(private);
	int i, ret;

	ret = i2c_smbus_read_byte_data(st->client, AD7998_ALERT_STAT_REG);
	if (ret <= 0)
		goto done;

	if (i2c_smbus_write_byte_data(st->client, AD7998_ALERT_STAT_REG,
		AD7998_ALERT_STAT_CLEAR) < 0)
		goto done;

	for (i = 0; i < 8; i++) {
		if (ret & BIT(i))
			iio_push_event(indio_dev,
				       i & 0x1 ?
				       IIO_UNMOD_EVENT_CODE(IIO_VOLTAGE,
							    (i >> 1),
							    IIO_EV_TYPE_THRESH,
							    IIO_EV_DIR_RISING) :
				       IIO_UNMOD_EVENT_CODE(IIO_VOLTAGE,
							    (i >> 1),
							    IIO_EV_TYPE_THRESH,
							    IIO_EV_DIR_FALLING),
				       iio_get_time_ns(indio_dev));
	}

done:
	return IRQ_HANDLED;
}