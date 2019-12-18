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
struct tsl2772_chip {int tsl2772_chip_status; int /*<<< orphan*/  als_mutex; int /*<<< orphan*/  prox_mutex; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int TSL2772_CHIP_WORKING ; 
 struct tsl2772_chip* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int tsl2772_chip_off (struct iio_dev*) ; 
 int tsl2772_chip_on (struct iio_dev*) ; 

__attribute__((used)) static int tsl2772_invoke_change(struct iio_dev *indio_dev)
{
	struct tsl2772_chip *chip = iio_priv(indio_dev);
	int device_status = chip->tsl2772_chip_status;
	int ret;

	mutex_lock(&chip->als_mutex);
	mutex_lock(&chip->prox_mutex);

	if (device_status == TSL2772_CHIP_WORKING) {
		ret = tsl2772_chip_off(indio_dev);
		if (ret < 0)
			goto unlock;
	}

	ret = tsl2772_chip_on(indio_dev);

unlock:
	mutex_unlock(&chip->prox_mutex);
	mutex_unlock(&chip->als_mutex);

	return ret;
}