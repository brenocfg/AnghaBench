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
struct tsl2563_chip {int /*<<< orphan*/  lock; int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int TSL2563_CMD ; 
 int TSL2563_REG_INT ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int) ; 
 struct tsl2563_chip* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tsl2563_read_interrupt_config(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_direction dir)
{
	struct tsl2563_chip *chip = iio_priv(indio_dev);
	int ret;

	mutex_lock(&chip->lock);
	ret = i2c_smbus_read_byte_data(chip->client,
				       TSL2563_CMD | TSL2563_REG_INT);
	mutex_unlock(&chip->lock);
	if (ret < 0)
		return ret;

	return !!(ret & 0x30);
}