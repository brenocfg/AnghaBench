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
struct mag3110_data {int /*<<< orphan*/  client; } ;
struct iio_poll_func {struct iio_dev* indio_dev; } ;
struct iio_dev {int /*<<< orphan*/  trig; int /*<<< orphan*/  active_scan_mask; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  MAG3110_DIE_TEMP ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct mag3110_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int mag3110_read (struct mag3110_data*,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t mag3110_trigger_handler(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct mag3110_data *data = iio_priv(indio_dev);
	u8 buffer[16]; /* 3 16-bit channels + 1 byte temp + padding + ts */
	int ret;

	ret = mag3110_read(data, (__be16 *) buffer);
	if (ret < 0)
		goto done;

	if (test_bit(3, indio_dev->active_scan_mask)) {
		ret = i2c_smbus_read_byte_data(data->client,
			MAG3110_DIE_TEMP);
		if (ret < 0)
			goto done;
		buffer[6] = ret;
	}

	iio_push_to_buffers_with_timestamp(indio_dev, buffer,
		iio_get_time_ns(indio_dev));

done:
	iio_trigger_notify_done(indio_dev->trig);
	return IRQ_HANDLED;
}