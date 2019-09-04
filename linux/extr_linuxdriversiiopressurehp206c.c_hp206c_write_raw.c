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
struct iio_chan_spec {int type; } ;
struct hp206c_data {int /*<<< orphan*/  mutex; void* pres_osr_index; void* temp_osr_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 long IIO_CHAN_INFO_OVERSAMPLING_RATIO ; 
#define  IIO_PRESSURE 129 
#define  IIO_TEMP 128 
 void* find_closest_descending (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp206c_osr_rates ; 
 struct hp206c_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hp206c_write_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int val, int val2, long mask)
{
	int ret = 0;
	struct hp206c_data *data = iio_priv(indio_dev);

	if (mask != IIO_CHAN_INFO_OVERSAMPLING_RATIO)
		return -EINVAL;
	mutex_lock(&data->mutex);
	switch (chan->type) {
	case IIO_TEMP:
		data->temp_osr_index = find_closest_descending(val,
			hp206c_osr_rates, ARRAY_SIZE(hp206c_osr_rates));
		break;
	case IIO_PRESSURE:
		data->pres_osr_index = find_closest_descending(val,
			hp206c_osr_rates, ARRAY_SIZE(hp206c_osr_rates));
		break;
	default:
		ret = -EINVAL;
	}
	mutex_unlock(&data->mutex);
	return ret;
}