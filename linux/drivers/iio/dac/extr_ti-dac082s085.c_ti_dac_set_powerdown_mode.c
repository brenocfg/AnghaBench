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
struct ti_dac_chip {unsigned int powerdown_mode; int /*<<< orphan*/  lock; scalar_t__ powerdown; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  POWERDOWN (unsigned int) ; 
 struct ti_dac_chip* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ti_dac_cmd (struct ti_dac_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ti_dac_set_powerdown_mode(struct iio_dev *indio_dev,
				     const struct iio_chan_spec *chan,
				     unsigned int mode)
{
	struct ti_dac_chip *ti_dac = iio_priv(indio_dev);
	int ret = 0;

	if (ti_dac->powerdown_mode == mode)
		return 0;

	mutex_lock(&ti_dac->lock);
	if (ti_dac->powerdown) {
		ret = ti_dac_cmd(ti_dac, POWERDOWN(mode), 0);
		if (ret)
			goto out;
	}
	ti_dac->powerdown_mode = mode;

out:
	mutex_unlock(&ti_dac->lock);
	return ret;
}