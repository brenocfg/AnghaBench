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
typedef  int /*<<< orphan*/  u8 ;
struct tcs3472_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  enable; int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int /*<<< orphan*/  TCS3472_ENABLE ; 
 int /*<<< orphan*/  TCS3472_ENABLE_AIEN ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tcs3472_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tcs3472_write_event_config(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_direction dir, int state)
{
	struct tcs3472_data *data = iio_priv(indio_dev);
	int ret = 0;
	u8 enable_old;

	mutex_lock(&data->lock);

	enable_old = data->enable;

	if (state)
		data->enable |= TCS3472_ENABLE_AIEN;
	else
		data->enable &= ~TCS3472_ENABLE_AIEN;

	if (enable_old != data->enable) {
		ret = i2c_smbus_write_byte_data(data->client, TCS3472_ENABLE,
						data->enable);
		if (ret)
			data->enable = enable_old;
	}
	mutex_unlock(&data->lock);

	return ret;
}