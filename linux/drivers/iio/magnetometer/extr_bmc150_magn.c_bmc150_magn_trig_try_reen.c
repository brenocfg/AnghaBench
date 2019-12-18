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
struct iio_trigger {int dummy; } ;
struct iio_dev {int dummy; } ;
struct bmc150_magn_data {int /*<<< orphan*/  mutex; int /*<<< orphan*/  dready_trigger_on; } ;

/* Variables and functions */
 int bmc150_magn_reset_intr (struct bmc150_magn_data*) ; 
 struct bmc150_magn_data* iio_priv (struct iio_dev*) ; 
 struct iio_dev* iio_trigger_get_drvdata (struct iio_trigger*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bmc150_magn_trig_try_reen(struct iio_trigger *trig)
{
	struct iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	struct bmc150_magn_data *data = iio_priv(indio_dev);
	int ret;

	if (!data->dready_trigger_on)
		return 0;

	mutex_lock(&data->mutex);
	ret = bmc150_magn_reset_intr(data);
	mutex_unlock(&data->mutex);

	return ret;
}