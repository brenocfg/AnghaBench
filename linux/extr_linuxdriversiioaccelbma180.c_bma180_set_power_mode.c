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
struct iio_chan_spec {int dummy; } ;
struct bma180_data {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int bma180_set_pmode (struct bma180_data*,unsigned int) ; 
 struct bma180_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bma180_set_power_mode(struct iio_dev *indio_dev,
		const struct iio_chan_spec *chan, unsigned int mode)
{
	struct bma180_data *data = iio_priv(indio_dev);
	int ret;

	mutex_lock(&data->mutex);
	ret = bma180_set_pmode(data, mode);
	mutex_unlock(&data->mutex);

	return ret;
}