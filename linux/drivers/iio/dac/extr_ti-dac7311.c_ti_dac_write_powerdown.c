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
struct ti_dac_chip {int powerdown; int /*<<< orphan*/  lock; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct ti_dac_chip* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int strtobool (char const*,int*) ; 
 int ti_dac_cmd (struct ti_dac_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_dac_get_power (struct ti_dac_chip*,int) ; 

__attribute__((used)) static ssize_t ti_dac_write_powerdown(struct iio_dev *indio_dev,
				      uintptr_t private,
				      const struct iio_chan_spec *chan,
				      const char *buf, size_t len)
{
	struct ti_dac_chip *ti_dac = iio_priv(indio_dev);
	bool powerdown;
	u8 power;
	int ret;

	ret = strtobool(buf, &powerdown);
	if (ret)
		return ret;

	power = ti_dac_get_power(ti_dac, powerdown);

	mutex_lock(&ti_dac->lock);
	ret = ti_dac_cmd(ti_dac, power, 0);
	if (!ret)
		ti_dac->powerdown = powerdown;
	mutex_unlock(&ti_dac->lock);

	return ret ? ret : len;
}