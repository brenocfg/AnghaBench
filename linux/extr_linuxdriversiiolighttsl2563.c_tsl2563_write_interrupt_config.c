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
struct tsl2563_chip {int intr; int int_enabled; int /*<<< orphan*/  lock; int /*<<< orphan*/  poweroff_work; int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int HZ ; 
 int TSL2563_CMD ; 
 int TSL2563_REG_INT ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int,int) ; 
 struct tsl2563_chip* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int tsl2563_configure (struct tsl2563_chip*) ; 
 int /*<<< orphan*/  tsl2563_get_power (struct tsl2563_chip*) ; 
 int tsl2563_set_power (struct tsl2563_chip*,int) ; 

__attribute__((used)) static int tsl2563_write_interrupt_config(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_direction dir, int state)
{
	struct tsl2563_chip *chip = iio_priv(indio_dev);
	int ret = 0;

	mutex_lock(&chip->lock);
	if (state && !(chip->intr & 0x30)) {
		chip->intr &= ~0x30;
		chip->intr |= 0x10;
		/* ensure the chip is actually on */
		cancel_delayed_work(&chip->poweroff_work);
		if (!tsl2563_get_power(chip)) {
			ret = tsl2563_set_power(chip, 1);
			if (ret)
				goto out;
			ret = tsl2563_configure(chip);
			if (ret)
				goto out;
		}
		ret = i2c_smbus_write_byte_data(chip->client,
						TSL2563_CMD | TSL2563_REG_INT,
						chip->intr);
		chip->int_enabled = true;
	}

	if (!state && (chip->intr & 0x30)) {
		chip->intr &= ~0x30;
		ret = i2c_smbus_write_byte_data(chip->client,
						TSL2563_CMD | TSL2563_REG_INT,
						chip->intr);
		chip->int_enabled = false;
		/* now the interrupt is not enabled, we can go to sleep */
		schedule_delayed_work(&chip->poweroff_work, 5 * HZ);
	}
out:
	mutex_unlock(&chip->lock);

	return ret;
}